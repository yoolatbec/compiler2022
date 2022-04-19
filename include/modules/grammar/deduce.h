/*
 * deduce.h
 *
 *  Created on: 2022年4月19日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_GRAMMAR_DEDUCE_H_
#define INCLUDE_MODULES_GRAMMAR_DEDUCE_H_

#include <modules/grammar/grammar_util.h>
#include <utils/linked_list.h>

sGrammar* init_all_grammar();

void deduce(sGrammar* start_grammar, sLinkedListNode** primitives);

#endif /* INCLUDE_MODULES_GRAMMAR_DEDUCE_H_ */
