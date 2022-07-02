/*
 * grammar_util.h
 *
 *  Created on: 2022年4月14日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_GRAMMAR_GRAMMAR_UTIL_H_
#define INCLUDE_MODULES_GRAMMAR_GRAMMAR_UTIL_H_

#include <modules/grammar/grammar.h>

/**
 * 使用的文法:
 * Expressions
 * 	: Definition ; Expressions
 * 	| Assignment ; Expressions
 * 	| IfStatement Expressions
 * 	| WhileStatement Expressions
 * 	| null
 * 	;
 *
 * Definition
 * 	: int identifier
 * 	;
 *
 * Assignment
 * 	: identifier = AdditiveStatement
 * 	;
 *
 * AdditiveStatement
 * 	: MultiplicativeStatement AdditiveStatement_
 * 	;
 * AdditiveStatement_
 * 	: null
 * 	| + MultiplicativeStatement AdditiveStatement_
 * 	| - MultiplicativeStatement AdditiveStatement_
 * 	;
 *
 * MultiplicativeStatement
 * 	: Term MultiplicativeStatement_
 * 	;
 *
 * MultiplicativeStatement_
 * 	: * Term MultiplicativeStatement_
 * 	| / Term MultiplicativeStatement_
 * 	| % Term MultiplicativeStatement_
 * 	| null
 * 	;
 *
 * Term
 * 	: identifier
 * 	| integer
 * 	| ( AdditiveStatement )
 * 	;
 *
 * IfStatement
 * 	: if ( BooleanStatement ) { Expressions } ElseStatement
 * 	;
 * ElseStatement
 * 	: null
 * 	| else { Expressions }
 * 	;
 *
 * WhileStatement
 * 	: while ( BooleanStatement ) { Expressions }
 * 	;
 *
 * BooleanStatement
 * 	: AdditiveStatement RelativeOperator AdditiveStatement
 * 	;
 *
 * RelativeOperator
 * 	: > | < | >= | <= | != | ==
 */

void grammar_construct_expressions(sGrammar**, sGrammar*, sGrammar*, sGrammar*,
		sGrammar*);  //构建Expressions文法
sGrammar* grammar_construct_definition();  //构建Definition文法
sGrammar* grammar_construct_assignment(sGrammar*);  //构建Assignment文法
void grammar_construct_additive_statement(sGrammar**, sGrammar*, sGrammar*);  //构建AdditiveStatement文法
sGrammar* grammar_construct_additive_statement_(sGrammar*);  //构建AdditiveStatement_文法
sGrammar* grammar_construct_multiplicative_statement(sGrammar*, sGrammar*);  //构建MultiplicativeStatement文法
sGrammar* grammar_construct_multiplicative_statement_(sGrammar*);  //构建MultiplicativeStatement_文法
sGrammar* grammar_construct_term(sGrammar*);  //构建Term文法
sGrammar* grammar_construct_if_statement(sGrammar*, sGrammar*, sGrammar*);  //构建IfStatement文法
sGrammar* grammar_construct_else_statement(sGrammar*);  //构建ElseStatement文法
sGrammar* grammar_construct_while_statement(sGrammar*, sGrammar*);  //构建WhileStatement文法
sGrammar* grammar_construct_boolean_statement(sGrammar*, sGrammar*);  //构建BooleanStatement文法
sGrammar* grammar_construct_relative_operator();  //构建RelativeOperator文法

#endif /* INCLUDE_MODULES_GRAMMAR_GRAMMAR_UTIL_H_ */
