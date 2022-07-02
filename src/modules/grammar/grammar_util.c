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
#include<stdio.h>

void grammar_construct_expressions(sGrammar **grammar, sGrammar *definition,
		sGrammar *assignment, sGrammar *if_statement, sGrammar *while_statement) {
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_expressions__definition);
	sGrammarNode *b1n1 = grammar_node_new(0, definition);
	sGrammarNode *b1n2 = grammar_node_new(RW_ID_SEMICOLON, NULL);
	sGrammarNode *b1n3 = grammar_node_new(0, *grammar);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);

	sGrammarBody *b2 = grammar_body_new();
	grammar_body_add_by_func(b2, using_expressions__assignment);
	sGrammarNode *b2n1 = grammar_node_new(0, assignment);
	sGrammarNode *b2n2 = grammar_node_new(RW_ID_SEMICOLON, NULL);
	sGrammarNode *b2n3 = grammar_node_new(0, *grammar);
	grammar_body_append(b2, b2n1);
	grammar_body_append(b2, b2n2);
	grammar_body_append(b2, b2n3);

	sGrammarBody *b3 = grammar_body_new();
	grammar_body_add_by_func(b3, using_expressions__if_statement);
	sGrammarNode *b3n1 = grammar_node_new(0, if_statement);
	sGrammarNode *b3n2 = grammar_node_new(0, *grammar);
	grammar_body_append(b3, b3n1);
	grammar_body_append(b3, b3n2);

	sGrammarBody *b4 = grammar_body_new();
	grammar_body_add_by_func(b4, using_expressions__while_statement);
	sGrammarNode *b4n1 = grammar_node_new(0, while_statement);
	sGrammarNode *b4n2 = grammar_node_new(0, *grammar);
	grammar_body_append(b4, b4n1);
	grammar_body_append(b4, b4n2);

	sGrammarBody *b5 = grammar_body_new();
	sGrammarNode *b5n1 = grammar_node_new(0, NULL);
	grammar_body_add_by_func(b5, using_expressions__null);
	grammar_body_append(b5, b5n1);

	grammar_add(*grammar, b1);
	grammar_add(*grammar, b2);
	grammar_add(*grammar, b3);
	grammar_add(*grammar, b4);
	grammar_add(*grammar, b5);
}

sGrammar* grammar_construct_definition() {
	sGrammar *grammar = grammar_new("definition");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_definition__int_identifier);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_INT, NULL);
	sGrammarNode *b1n2 = grammar_node_new(PRIM_ID_IDENTIFIER, NULL);
	grammar_node_set_function(b1n2, new_var);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);

	grammar_add(grammar, b1);

	return grammar;
}

sGrammar* grammar_construct_assignment(sGrammar *as) {
	sGrammar *grammar = grammar_new("assignment");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_assignment__identifier_assign_as);
	sGrammarNode *b1n1 = grammar_node_new(PRIM_ID_IDENTIFIER, NULL);
	grammar_node_set_function(b1n1, load_var_addr);
	sGrammarNode *b1n2 = grammar_node_new(RW_ID_ASSIGN, NULL);
	sGrammarNode *b1n3 = grammar_node_new(0, as);
	sGrammarNode *bnf = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf, store_var);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);
	grammar_body_append(b1, bnf);

	grammar_add(grammar, b1);

	return grammar;
}

void grammar_construct_additive_statement(sGrammar **grammar, sGrammar *ms,
		sGrammar *as_) {
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_as__ms_as_);
	sGrammarNode *b1n1 = grammar_node_new(0, ms);
	sGrammarNode *b1n2 = grammar_node_new(0, as_);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);

	grammar_add(*grammar, b1);
}

sGrammar* grammar_construct_additive_statement_(sGrammar *ms) {
	sGrammar *grammar = grammar_new("additive statement_");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_as__plus_as);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_PLUS, NULL);
	grammar_node_set_function(b1n1, push_ops);
	sGrammarNode *b1n2 = grammar_node_new(0, ms);
	sGrammarNode *b1n3 = grammar_node_new(0, grammar);
	sGrammarNode *bnf = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf, create_IR);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);
	grammar_body_append(b1, bnf);

	sGrammarBody *b2 = grammar_body_new();
	grammar_body_add_by_func(b2, using_as__minus_as);
	sGrammarNode *b2n1 = grammar_node_new(RW_ID_MINUS, NULL);
	grammar_node_set_function(b2n1, push_ops);
	sGrammarNode *b2n2 = grammar_node_new(0, ms);
	sGrammarNode *b2n3 = grammar_node_new(0, grammar);
	grammar_body_append(b2, b2n1);
	grammar_body_append(b2, b2n2);
	grammar_body_append(b2, b2n3);
	grammar_body_append(b2, bnf);

	sGrammarBody *b3 = grammar_body_new();
	sGrammarNode *b3n1 = grammar_node_new(0, NULL);
	grammar_body_append(b3, b3n1);

	grammar_add(grammar, b1);
	grammar_add(grammar, b2);
	grammar_add(grammar, b3);

	return grammar;
}

sGrammar* grammar_construct_multiplicative_statement(sGrammar *term,
		sGrammar *ms_) {
	sGrammar *grammar = grammar_new("multiplicative statement");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_ms__term_ms_);
	sGrammarNode *b1n1 = grammar_node_new(0, term);
	sGrammarNode *b1n2 = grammar_node_new(0, ms_);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_add(grammar, b1);

	return grammar;
}

sGrammar* grammar_construct_multiplicative_statement_(sGrammar *term) {
	sGrammar *grammar = grammar_new("multiplicative statement_");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_ms__ast_ms);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_AST, NULL);
	grammar_node_set_function(b1n1, push_ops);
	sGrammarNode *b1n2 = grammar_node_new(0, term);
	sGrammarNode *b1n3 = grammar_node_new(0, grammar);
	sGrammarNode *bnf = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf, create_IR);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);
	grammar_body_append(b1, bnf);

	sGrammarBody *b2 = grammar_body_new();
	grammar_body_add_by_func(b2, using_ms__slash_ms);
	sGrammarNode *b2n1 = grammar_node_new(RW_ID_SLASH, NULL);
	grammar_node_set_function(b2n1, push_ops);
	sGrammarNode *b2n2 = grammar_node_new(0, term);
	sGrammarNode *b2n3 = grammar_node_new(0, grammar);
	grammar_body_append(b2, b2n1);
	grammar_body_append(b2, b2n2);
	grammar_body_append(b2, b2n3);
	grammar_body_append(b2, bnf);

	sGrammarBody *b3 = grammar_body_new();
	grammar_body_add_by_func(b3, using_ms__percent_ms);
	sGrammarNode *b3n1 = grammar_node_new(RW_ID_PERCENT, NULL);
	grammar_node_set_function(b3n1, push_ops);
	sGrammarNode *b3n2 = grammar_node_new(0, term);
	sGrammarNode *b3n3 = grammar_node_new(0, grammar);
	grammar_body_append(b3, b3n1);
	grammar_body_append(b3, b3n2);
	grammar_body_append(b3, b3n3);
	grammar_body_append(b3, bnf);

	sGrammarBody *b4 = grammar_body_new();
	sGrammarNode *b4n1 = grammar_node_new(0, NULL);
	grammar_body_append(b4, b4n1);

	grammar_add(grammar, b1);
	grammar_add(grammar, b2);
	grammar_add(grammar, b3);
	grammar_add(grammar, b4);

	return grammar;
}

sGrammar* grammar_construct_term(sGrammar *additive_statement) {
	sGrammar *grammar = grammar_new("term");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_term__identifier);
	sGrammarNode *b1n1 = grammar_node_new(PRIM_ID_IDENTIFIER, NULL);
	grammar_node_set_function(b1n1, load_var);
	grammar_body_append(b1, b1n1);

	sGrammarBody *b2 = grammar_body_new();
	grammar_body_add_by_func(b2, using_term__integer);
	sGrammarNode *b2n1 = grammar_node_new(PRIM_ID_INTEGER, NULL);
	grammar_node_set_function(b2n1, push_imme);
	grammar_body_append(b2, b2n1);

	sGrammarBody *b3 = grammar_body_new();
	grammar_body_add_by_func(b3,
			using_term__parenthesis_left_additive_statement_parenthesis_right);
	sGrammarNode *b3n1 = grammar_node_new(RW_ID_PARENTHESIS_LEFT, NULL);
	sGrammarNode *b3n2 = grammar_node_new(0, additive_statement);
	sGrammarNode *b3n3 = grammar_node_new(RW_ID_PARENTHESIS_RIGHT, NULL);
	grammar_body_append(b3, b3n1);
	grammar_body_append(b3, b3n2);
	grammar_body_append(b3, b3n3);

	grammar_add(grammar, b1);
	grammar_add(grammar, b2);
	grammar_add(grammar, b3);

	return grammar;
}

sGrammar* grammar_construct_if_statement(sGrammar *boolean_statement,
		sGrammar *expressions, sGrammar *else_statement) {
	sGrammar *grammar = grammar_new("if statement");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_if_statement);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_IF, NULL);
	grammar_node_set_function(b1n1, load_label_stack_if);
	sGrammarNode *bnf4 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf4, create_goto);
	sGrammarNode *bnf6 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf6, create_label);
	sGrammarNode *b1n2 = grammar_node_new(RW_ID_PARENTHESIS_LEFT, NULL);
	grammar_node_set_function(b1n2, switch_list);
	sGrammarNode *b1n3 = grammar_node_new(0, boolean_statement);
	sGrammarNode *b1n4 = grammar_node_new(RW_ID_PARENTHESIS_RIGHT, NULL);
	grammar_node_set_function(b1n4, switch_back_list);
	sGrammarNode *b1n5 = grammar_node_new(RW_ID_BRACE_LEFT, NULL);
	sGrammarNode *b1n6 = grammar_node_new(0, expressions);
	sGrammarNode *bnf5 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf5, create_goto);
	sGrammarNode *b1n7 = grammar_node_new(RW_ID_BRACE_RIGHT, NULL);
	grammar_node_set_function(b1n7, create_label);
	sGrammarNode *bnf1 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf1, append_conditional_list);
	sGrammarNode *bnf3 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf3, create_if);
	sGrammarNode *b1n8 = grammar_node_new(0, else_statement);
	sGrammarNode *bnf2 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf2, create_label);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, bnf4);
	grammar_body_append(b1, bnf6);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);
	grammar_body_append(b1, b1n4);
	grammar_body_append(b1, b1n5);
	grammar_body_append(b1, b1n6);
	grammar_body_append(b1, bnf5);
	grammar_body_append(b1, b1n7);
	grammar_body_append(b1, bnf1);
	grammar_body_append(b1, bnf3);
	grammar_body_append(b1, b1n8);
	grammar_body_append(b1, bnf2);
	grammar_add(grammar, b1);

	return grammar;
}

sGrammar* grammar_construct_else_statement(sGrammar *expressions) {
	sGrammar *grammar = grammar_new("else statement");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_else_statement);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_ELSE, NULL);
	sGrammarNode *b1n2 = grammar_node_new(RW_ID_BRACE_LEFT, NULL);
	sGrammarNode *b1n3 = grammar_node_new(0, expressions);
	sGrammarNode *b1n4 = grammar_node_new(RW_ID_BRACE_RIGHT, NULL);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);
	grammar_body_append(b1, b1n4);
	grammar_add(grammar, b1);

	sGrammarBody *b2 = grammar_body_new();
	sGrammarNode *b2n1 = grammar_node_new(0, NULL);
	grammar_body_append(b2, b2n1);
	grammar_add(grammar, b2);

	return grammar;
}

sGrammar* grammar_construct_while_statement(sGrammar *boolean_statement,
		sGrammar *expressions) {
	sGrammar *grammar = grammar_new("while statement");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1, using_while_statement);
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_WHILE, NULL);
	grammar_node_set_function(b1n1, load_label_stack_while);
	sGrammarNode *bnf1 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf1, create_goto);
	sGrammarNode *bnf2 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf2, create_label);
	sGrammarNode *b1n2 = grammar_node_new(RW_ID_PARENTHESIS_LEFT, NULL);
	grammar_node_set_function(b1n2, switch_list);
	sGrammarNode *b1n3 = grammar_node_new(0, boolean_statement);
	sGrammarNode *b1n4 = grammar_node_new(RW_ID_PARENTHESIS_RIGHT, NULL);
	grammar_node_set_function(b1n4, switch_back_list);
	sGrammarNode *b1n5 = grammar_node_new(RW_ID_BRACE_LEFT, NULL);
	sGrammarNode *b1n6 = grammar_node_new(0, expressions);
	sGrammarNode *b1n7 = grammar_node_new(RW_ID_BRACE_RIGHT, NULL);
	grammar_node_set_function(b1n7, create_label);
	sGrammarNode *bnf3 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf3, append_conditional_list);
	sGrammarNode *bnf4 = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf4, create_while);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, bnf1);
	grammar_body_append(b1, bnf2);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);
	grammar_body_append(b1, b1n4);
	grammar_body_append(b1, b1n5);
	grammar_body_append(b1, b1n6);
	grammar_body_append(b1, b1n7);
	grammar_body_append(b1, bnf3);
	grammar_body_append(b1, bnf4);
	grammar_add(grammar, b1);

	return grammar;
}

sGrammar* grammar_construct_boolean_statement(sGrammar *additive_statement,
		sGrammar *relative_operator) {
	sGrammar *grammar = grammar_new("boolean statement");
	sGrammarBody *b1 = grammar_body_new();
	grammar_body_add_by_func(b1,
			using_boolean_statement__as_relative_operator_as);
	sGrammarNode *b1n1 = grammar_node_new(0, additive_statement);
	sGrammarNode *b1n2 = grammar_node_new(0, relative_operator);
	sGrammarNode *b1n3 = grammar_node_new(0, additive_statement);
	sGrammarNode *bnf = grammar_node_new(0, NULL);
	grammar_node_set_function(bnf, create_IR);
	grammar_body_append(b1, b1n1);
	grammar_body_append(b1, b1n2);
	grammar_body_append(b1, b1n3);
	grammar_body_append(b1, bnf);
	grammar_add(grammar, b1);

	return grammar;
}

sGrammar* grammar_construct_relative_operator() {
	sGrammar *grammar = grammar_new("relative operator");
	sGrammarBody *b1 = grammar_body_new();
	sGrammarNode *b1n1 = grammar_node_new(RW_ID_LESS_THAN, NULL);
	grammar_node_set_function(b1n1, push_ops);
	grammar_body_add_by_func(b1, using_relative_operator__less_than);
	grammar_body_append(b1, b1n1);
	grammar_add(grammar, b1);

	sGrammarBody *b2 = grammar_body_new();
	sGrammarNode *b2n1 = grammar_node_new(RW_ID_GREATER_THAN, NULL);
	grammar_node_set_function(b2n1, push_ops);
	grammar_body_add_by_func(b2, using_relative_operator__greater_than);
	grammar_body_append(b2, b2n1);
	grammar_add(grammar, b2);

	sGrammarBody *b3 = grammar_body_new();
	sGrammarNode *b3n1 = grammar_node_new(RW_ID_LESS_EQUAL, NULL);
	grammar_node_set_function(b3n1, push_ops);
	grammar_body_add_by_func(b3, using_relative_operator__less_equal);
	grammar_body_append(b3, b3n1);
	grammar_add(grammar, b3);

	sGrammarBody *b4 = grammar_body_new();
	sGrammarNode *b4n1 = grammar_node_new(RW_ID_GREATER_EQUAL, NULL);
	grammar_node_set_function(b4n1, push_ops);
	grammar_body_add_by_func(b4, using_relative_operator__greater_equal);
	grammar_body_append(b4, b4n1);
	grammar_add(grammar, b4);

	sGrammarBody *b5 = grammar_body_new();
	sGrammarNode *b5n1 = grammar_node_new(RW_ID_EQUAL, NULL);
	grammar_node_set_function(b5n1, push_ops);
	grammar_body_add_by_func(b5, using_relative_operator__equal);
	grammar_body_append(b5, b5n1);
	grammar_add(grammar, b5);

	sGrammarBody *b6 = grammar_body_new();
	sGrammarNode *b6n1 = grammar_node_new(RW_ID_NOT_EQUAL, NULL);
	grammar_node_set_function(b6n1, push_ops);
	grammar_body_add_by_func(b6, using_relative_operator__not_equal);
	grammar_body_append(b6, b6n1);
	grammar_add(grammar, b6);

	return grammar;
}
