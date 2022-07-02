/*
 * by_func.h
 *
 *  Created on: 2022年4月19日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_GRAMMAR_BY_FUNC_H_
#define INCLUDE_MODULES_GRAMMAR_BY_FUNC_H_

/*
 * 匹配过程中的辅助函数，用于提示使用的产生式，不影响匹配过程
 */

void using_relative_operator__equal();
void using_relative_operator__not_equal();
void using_relative_operator__less_than();
void using_relative_operator__less_equal();
void using_relative_operator__greater_than();
void using_relative_operator__greater_equal();

void using_boolean_statement__as_relative_operator_as();

void using_while_statement();
void using_else_statement();
void using_if_statement();

void using_term__identifier();
void using_term__integer();
void using_term__parenthesis_left_additive_statement_parenthesis_right();

void using_ms__term_ms_();

void using_ms__ast_ms();
void using_ms__slash_ms();
void using_ms__percent_ms();

void using_as__plus_as();
void using_as__minus_as();

void using_as__ms_as_();

void using_assignment__identifier_assign_as();
void using_definition__int_identifier();

void using_expressions__definition();
void using_expressions__assignment();
void using_expressions__if_statement();
void using_expressions__while_statement();
void using_expressions__null();

#endif /* INCLUDE_MODULES_GRAMMAR_BY_FUNC_H_ */
