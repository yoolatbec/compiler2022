/*
 * symbol.c
 *
 *  Created on: 2022年5月19日
 *      Author: yoolatbec
 */

#include <modules/symbol/symbol.h>
#include <utils/linked_list.h>
#include <reserved_word.h>

struct sSymbol {
	char *name;
	int hashcode;
	int type;
	void *value;
};

struct sSymbolTable {
	sLinkedListNode* symbols;
};
