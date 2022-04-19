/*
 * by_func.c
 *
 *  Created on: 2022年4月19日
 *      Author: yoolatbec
 */

#include <modules/grammar/by_func.h>
#include <stdio.h>

void using_l0a__l1a_l0b() {
	puts("using l0a -> l1a l0b");
}

void using_l0b__plus_l1a_l0b() {
	puts("using l0b -> + l1a l0b");
}

void using_l0b__minus_l1a_l0b() {
	puts("using l0b -> - l1a l0b");
}

void using_l0b__null() {
	puts("using l0b -> null");
}

void using_l1a__term_l1b() {
	puts("using l1a -> term l1b");
}

void using_l1b__ast_term_l1b() {
	puts("using l1b -> * term l1b");
}

void using_l1b__slash_term_l1b() {
	puts("using l1b -> / term l1b");
}

void using_l1b__percent_term_l1b() {
	puts("using l1b -> % term l1b");
}

void using_l1b__null() {
	puts("using l1b -> null");
}

void using_term__minus_uint() {
	puts("using term -> - int");
}

void using_term__uint() {
	puts("using term -> int");
}

void using_term__parenthesis_left_l0a_parenthesis_right() {
	puts("using term -> ( l0a )");
}
