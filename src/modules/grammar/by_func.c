/*
 * by_func.c
 *
 *  Created on: 2022年4月19日
 *      Author: yoolatbec
 */

#include <modules/grammar/by_func.h>
#include <stdio.h>

void using_relative_operator__equal(){
	puts("using relative operator -> ==");
}

void using_relative_operator__not_equal(){
	puts("using relative operator -> !=");
}

void using_relative_operator__less_than(){
	puts("using relative operator -> < ");
}

void using_relative_operator__less_equal(){
	puts("using relative operator -> <=");
}

void using_relative_operator__greater_than(){
	puts("using relative operator -> >");
}

void using_relative_operator__greater_equal(){
	puts("using relative operator -> >= ");
}

void using_boolean_statement__as_relative_operator_as(){
	puts("using boolean statement -> as relative operator as");
}

void using_while_statement(){
	puts("using while statement -> while ( boolean statement ) { expressions }");
}

void using_else_statement(){
	puts("using else statement -> else { expressions }");
}

void using_if_statement(){
	puts("using if statement -> if ( boolean statement ) { expressions }");
}

void using_term__identifier(){
	puts("using term -> identifier");
}

void using_term__integer(){
	puts("using term -> integer");
}

void using_term__parenthesis_left_additive_statement_parenthesis_right(){
	puts("using term -> ( as )");
}

void using_ms__term_ms_(){
	puts("using ms -> term ms_");
}

void using_ms__ast_ms(){
	puts("using ms_ -> * term ms_");
}

void using_ms__slash_ms(){
	puts("using ms_ -> / term ms_");
}

void using_ms__percent_ms(){
	puts("using ms_ -> % term ms_");
}

void using_as__plus_as(){
	puts("using as_ -> + ms as_");
}

void using_as__minus_as(){
	puts("using as_ -> - ms as_");
}

void using_as__ms_as_(){
	puts("using as -> ms as_");
}

void using_assignment__identifier_assign_as(){
	puts("using assignment -> identifier = as");
}

void using_definition__int_identifier(){
	puts("using definition -> int identifier");
}

void using_expressions__definition(){
	puts("using expressions -> definition ;");
}

void using_expressions__assignment(){
	puts("using expressions -> assignment ;");
}

void using_expressions__if_statement(){
	puts("using expressions -> if statement");
}

void using_expressions__while_statement(){
	puts("using expressions -> while statement");
}

void using_expressions__null(){
	puts("using expressions -> null");
}
