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
 * expected grammar:
 * L0a -> L1a L0b
 * L0b -> + L1a L0b | - L1a L0b | null
 * L1a -> Term L1b
 * L1b -> * Term L1b | / Term L1b | % Term L1b | null
 * Term -> - int | int | (L0a)
 */

sGrammar* grammar_construct_term();
sGrammar* grammar_construct_l1b(sGrammar*);
sGrammar* grammar_construct_l1a(sGrammar*, sGrammar*);
sGrammar* grammar_construct_l0b(sGrammar*);
sGrammar* grammar_construct_l0a(sGrammar*, sGrammar*);

#endif /* INCLUDE_MODULES_GRAMMAR_GRAMMAR_UTIL_H_ */
