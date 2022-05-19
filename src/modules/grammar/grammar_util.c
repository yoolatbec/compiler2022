/*
 * grammar_util.c
 *
 *  Created on: 2022年4月14日
 *      Author: yoolatbec
 */

#include <modules/grammar/grammar_util.h>
#include <stddef.h>
#include <modules/grammar/by_func.h>
#include <modules/grammar/grammar_tree.h>
#include <modules/ir/ir_func.h>

sGrammar* grammar_construct_term() {
	sGrammar *grammar = grammar_new("term");

	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_term__uint);
	sGrammarNode *b1n1 = grammar_node_new(PRIM_ID_INTEGER, NULL);
	grammar_node_set_function(b1n1, push_oprands);
	grammar_body_append(b1, b1n1);

	grammar_add(grammar, b1);

	sGrammarBody *b2 = grammar_body_new();
	grammar_body_add_by_func(b2, using_term__minus_uint);
	sGrammarNode *b2n1 = grammar_node_new(RW_ID_MINUS, NULL);
	sGrammarNode *b2n2 = grammar_node_new(PRIM_ID_INTEGER, NULL);
	grammar_body_append(b2, b2n1);
	grammar_body_append(b2, b2n2);

	grammar_add(grammar, b2);

	return grammar;
}

sGrammar* grammar_construct_l1b(sGrammar *term_grammar) {
	sGrammar *grammar = grammar_new("l1b");

	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_l1b__ast_term_l1b);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_AST, NULL);
	grammar_node_set_function(b1n1, push_ops);
	sGrammarNode *b1n2 = grammar_node_new(0, term_grammar);
	sGrammarNode* b1nf = grammar_node_new(0, NULL);
	grammar_node_set_function(b1nf, create_IR);
	sGrammarNode *b1n3 = grammar_node_new(0, grammar);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1nf);
	grammar_body_append(b1, b1n3);
	grammar_add(grammar, b1);

	sGrammarBody *b2 = grammar_body_new();
	grammar_body_add_by_func(b2, using_l1b__slash_term_l1b);
	sGrammarNode *b2n1 = grammar_node_new(RW_ID_SLASH, NULL);
	grammar_node_set_function(b2n1, push_ops);
	sGrammarNode *b2n2 = grammar_node_new(0, term_grammar);
	sGrammarNode* b2nf = grammar_node_new(0, NULL);
	grammar_node_set_function(b2nf, create_IR);
	sGrammarNode *b2n3 = grammar_node_new(0, grammar);
	grammar_body_append(b2, b2n1);
	grammar_body_append(b2, b2n2);
	grammar_body_append(b2, b2nf);
	grammar_body_append(b2, b2n3);
	grammar_add(grammar, b2);

	sGrammarBody *b3 = grammar_body_new();
	grammar_body_add_by_func(b3, using_l1b__percent_term_l1b);
	sGrammarNode *b3n1 = grammar_node_new(RW_ID_PERCENT, NULL);
	grammar_node_set_function(b3n1, push_ops);
	sGrammarNode *b3n2 = grammar_node_new(0, term_grammar);
	sGrammarNode* b3nf = grammar_node_new(0, NULL);
	grammar_node_set_function(b3nf, create_IR);
	sGrammarNode *b3n3 = grammar_node_new(0, grammar);
	grammar_body_append(b3, b3n1);
	grammar_body_append(b3, b3n2);
	grammar_body_append(b3, b3nf);
	grammar_body_append(b3, b3n3);
	grammar_add(grammar, b3);

	sGrammarBody *b4 = grammar_body_new();
	grammar_body_add_by_func(b4, using_l1b__null);
	sGrammarNode* b4n1 = grammar_node_new(0, NULL);
	grammar_body_append(b4, b4n1);
	grammar_add(grammar, b4);

	return grammar;
}

sGrammar* grammar_construct_l1a(sGrammar *l1b_grammar, sGrammar *term_grammar) {
	sGrammar *grammar = grammar_new("l1a");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_l1a__term_l1b);
	sGrammarNode *b1n1 = grammar_node_new(0, term_grammar);
	sGrammarNode *b1n2 = grammar_node_new(0, l1b_grammar);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_add(grammar, b1);

	return grammar;
}

sGrammar* grammar_construct_l0b(sGrammar *l1a_grammar) {
	sGrammar *grammar = grammar_new("l0b");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_l0b__plus_l1a_l0b);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_PLUS, NULL);
	grammar_node_set_function(b1n1, push_ops);
	sGrammarNode *b1n2 = grammar_node_new(0, l1a_grammar);
	sGrammarNode* b1nf = grammar_node_new(0, NULL);
	grammar_node_set_function(b1nf, create_IR);
	sGrammarNode *b1n3 = grammar_node_new(0, grammar);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1nf);
	grammar_body_append(b1, b1n3);
	grammar_add(grammar, b1);

	sGrammarBody *b2 = grammar_body_new();
	grammar_body_add_by_func(b2, using_l0b__minus_l1a_l0b);
	sGrammarNode *b2n1 = grammar_node_new(RW_ID_MINUS, NULL);
	grammar_node_set_function(b2n1, push_ops);
	sGrammarNode *b2n2 = grammar_node_new(0, l1a_grammar);
	sGrammarNode* b2nf = grammar_node_new(0, NULL);
	grammar_node_set_function(b2nf, create_IR);
	sGrammarNode *b2n3 = grammar_node_new(0, grammar);
	grammar_body_append(b2, b2n1);
	grammar_body_append(b2, b2n2);
	grammar_body_append(b2, b2nf);
	grammar_body_append(b2, b2n3);
	grammar_add(grammar, b2);

	sGrammarBody *b3 = grammar_body_new();
	grammar_body_add_by_func(b3, using_l0b__null);
	sGrammarNode* b3n1 = grammar_node_new(0, NULL);
	grammar_body_append(b3, b3n1);
	grammar_add(grammar, b3);

	return grammar;
}

sGrammar* grammar_construct_l0a(sGrammar *l1a_grammar, sGrammar *l0b_grammar) {
	sGrammar *grammar = grammar_new("l0a");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_l0a__l1a_l0b);
	sGrammarNode *b1n1 = grammar_node_new(0, l1a_grammar);
	sGrammarNode *b1n2 = grammar_node_new(0, l0b_grammar);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_add(grammar, b1);

	return grammar;
}
