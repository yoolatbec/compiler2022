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
	sGrammar *expression = grammar_new("expression");
	sGrammar *as = grammar_new("additive statement");
	sGrammar *term = grammar_construct_term(as);
	sGrammar *ms_ = grammar_construct_multiplicative_statement_(term);
	sGrammar *ms = grammar_construct_multiplicative_statement(term, ms_);
	sGrammar *as_ = grammar_construct_additive_statement_(ms);
	grammar_construct_additive_statement(&as, ms, as_);
	sGrammar *relative_operator = grammar_construct_relative_operator();
	sGrammar *boolean_statement = grammar_construct_boolean_statement(as,
			relative_operator);
	sGrammar *while_statement = grammar_construct_while_statement(
			boolean_statement, expression);
	sGrammar *else_statement = grammar_construct_else_statement(expression);
	sGrammar *if_statement = grammar_construct_if_statement(boolean_statement,
			expression, else_statement);
	sGrammar *assignment = grammar_construct_assignment(as);
	sGrammar *definition = grammar_construct_definition();
	grammar_construct_expressions(&expression, definition, assignment,
			if_statement, while_statement);

	return expression;
}

sLinkedListNode* deduce(sGrammar *start_grammar, sLinkedListNode **primitives) {
	//初始化变量
	sLinkedListNode *grammar_node_stack = NULL;  //语法栈
	sGrammar *current_grammar = NULL;  //当前语法
	sGrammarNode *current_grammar_node = NULL;  //当前节点
	sPrimitive *current_primitive = linked_list_first(*primitives);  //当前符号
	*primitives = linked_list_remove_first(*primitives);

	//用于构建中间表示的上下文
	sContext *context = (sContext*) malloc(sizeof(sContext));
	context->IRs = NULL;
	context->oprands = NULL;
	context->ops = NULL;
	context->label_base = 1 << 12;
	context->next_assign_label = 1 << 12;
	context->label_stack = NULL;
	context->variable = NULL;
	context->stack_offset = 0;

	while (*primitives != NULL || grammar_node_stack != NULL) {
		int type = primitive_get_type(current_primitive);

		if (current_grammar_node == NULL) {
			sGrammarBody *body = NULL;
			if (current_grammar == NULL) {
				//如果当前节点为空且产生式为空，则从开始文法开始
				body = grammar_get_first_body(start_grammar);
			} else {
				//如果当前节点为空而产生式不为空，则继续当前产生式
				body = grammar_get_first_body(current_grammar);
			}

			//用于判断一条语法能够推导出空
			int deduces_null = 0;

			//寻找合适的产生式
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
				//如果没有产生式可以推导，则试图推导出空
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
		} else {  //如果当前节点不为空
			if (grammar_node_is_function_node(current_grammar_node)) {
				//如果当前节点为动作节点，则执行动作
				grammar_node_function(current_grammar_node, context);
				current_grammar_node = grammar_node_get_next(
						current_grammar_node);
			} else if (grammar_node_get_type(current_grammar_node) != 0) {
				//如果当前节点匹配一个终结符号，则尝试匹配
				if (grammar_node_get_type(current_grammar_node) == type) {
					if (grammar_node_has_function(current_grammar_node)) {
						context->parameter = grammar_node_get_type(
								current_grammar_node);
						context->primitive = current_primitive;
						grammar_node_function(current_grammar_node, context);
					}

					current_grammar_node = grammar_node_get_next(
							current_grammar_node);
					current_primitive = linked_list_first(*primitives);
					*primitives = linked_list_remove_first(*primitives);

					//如果一条产生式匹配完成，则弹出语法栈顶端的产生式
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
				//如果当前节点匹配一个非终结符号
				//则将当前产生式入栈，将当前语法设置为该非终结符号对应的语法
				grammar_node_stack = linked_list_append(grammar_node_stack,
						grammar_node_get_next(current_grammar_node));
				current_grammar = grammar_node_get_value(current_grammar_node);
				current_grammar_node = NULL;
			}
		}
	}

	return context->IRs;
}

