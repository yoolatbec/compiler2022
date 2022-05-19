/*
 * deduce.c
 *
 *  Created on: 2022年4月19日
 *      Author: yoolatbec
 */

#include <modules/grammar/deduce.h>
#include <modules/lexical/primitive.h>
#include <stdio.h>
#include <modules/grammar/by_func.h>
#include <modules/grammar/grammar_tree.h>
#include <modules/ir/ir_func.h>
#include <stdlib.h>

sGrammar* init_all_grammar() {
	sGrammar *term_grammar = grammar_construct_term();
	sGrammar *l1b = grammar_construct_l1b(term_grammar);
	sGrammar *l1a = grammar_construct_l1a(l1b, term_grammar);
	sGrammar *l0b = grammar_construct_l0b(l1a);
	sGrammar *l0a = grammar_construct_l0a(l1a, l0b);

	sGrammarBody *body = grammar_body_new();
	grammar_body_add_by_func(body,
			using_term__parenthesis_left_l0a_parenthesis_right);
	sGrammarNode *n1 = grammar_node_new(RW_ID_PARENTHESIS_LEFT, NULL);
	sGrammarNode *n2 = grammar_node_new(0, l0a);
	sGrammarNode *n3 = grammar_node_new(RW_ID_PARENTHESIS_RIGHT, NULL);
	grammar_body_append(body, n1);
	grammar_body_append(body, n2);
	grammar_body_append(body, n3);
	grammar_add(term_grammar, body);

	return l0a;
}

sLinkedListNode* deduce(sGrammar *start_grammar, sLinkedListNode **primitives) {
	sLinkedListNode *grammar_node_stack = NULL;
	sGrammar *current_grammar = NULL;
	sGrammarNode *current_grammar_node = NULL;
	sPrimitive *current_primitive = linked_list_first(*primitives);
	*primitives = linked_list_remove_first(*primitives);
	sGrammarTreeNode *root_node = grammar_tree_node_new();
	sGrammarTreeNode *current_node = root_node;
	sContext *context = (sContext*) malloc(sizeof(sContext));
	context->IRs = NULL;
	context->oprands = NULL;
	context->ops = NULL;
	context->label_base = 1 << 12;
	context->next_assign_label = 1 << 12;

	while (*primitives != NULL || grammar_node_stack != NULL) {
		int type = primitive_get_type(current_primitive);

		if (current_grammar_node == NULL) {
			sGrammarBody *body = NULL;
			if (current_grammar == NULL) {
				body = grammar_get_first_body(start_grammar);
			} else {
				body = grammar_get_first_body(current_grammar);
			}

			int deduces_null = 0;

			while (body != NULL) {
				sLinkedListNode *firsts = grammar_body_get_firsts(body);

				if (linked_list_contains(firsts, NULL)) {
					deduces_null = 1;
				}

				if (linked_list_contains(firsts, (void*) type)) {
					break;
				}

				body = grammar_body_get_next(body);
			}

			if (body == NULL) {
				if (deduces_null == 1) {
					current_grammar_node = linked_list_last(grammar_node_stack);
					grammar_node_stack = linked_list_remove_last(
							grammar_node_stack);
				} else {
					//should throw an exception
				}
			} else {
				current_grammar_node = grammar_body_get_first_node(body);
				grammar_body_by_func(body);
			}
		} else {
			if (grammar_node_is_function_node(current_grammar_node)) {
				grammar_node_function(current_grammar_node, context);
				current_grammar_node = grammar_node_get_next(
						current_grammar_node);
			} else if (grammar_node_get_type(current_grammar_node) != 0) {
				if (grammar_node_get_type(current_grammar_node) == type) {
					if (grammar_node_has_function(current_grammar_node)) {
						context->parameter = grammar_node_get_type(
								current_grammar_node);
						grammar_node_function(current_grammar_node, context);
					}

					current_grammar_node = grammar_node_get_next(
							current_grammar_node);
					current_primitive = linked_list_first(*primitives);
					*primitives = linked_list_remove_first(*primitives);

					if (current_grammar_node == NULL) {
						current_grammar_node = linked_list_last(
								grammar_node_stack);
						grammar_node_stack = linked_list_remove_last(
								grammar_node_stack);
					}
				} else {
					//should throw an exception
				}
			} else {
				grammar_node_stack = linked_list_append(grammar_node_stack,
						grammar_node_get_next(current_grammar_node));
				current_grammar = grammar_node_get_value(current_grammar_node);
				current_grammar_node = NULL;
			}
		}
	}

	return context->IRs;
}

