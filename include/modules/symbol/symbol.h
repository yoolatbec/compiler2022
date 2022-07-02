/*
 * symbol.h
 *
 *  Created on: 2022年5月19日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_SYMBOL_SYMBOL_H_
#define INCLUDE_MODULES_SYMBOL_SYMBOL_H_

typedef struct sSymbolTable sSymbolTable;
typedef struct sSymbol sSymbol;

sSymbol* new_symbol(char*, int, int, void*);

sSymbolTable* new_symbol_table();

void symbol_table_insert(sSymbolTable*, sSymbol*);
sSymbol* symbol_table_search(sSymbolTable*, int);
sSymbol* symbol_table_search_by_name(sSymbolTable*, char*);

void* symbol_get_value(sSymbol*);
int symbol_get_type(sSymbol*);

#endif /* INCLUDE_MODULES_SYMBOL_SYMBOL_H_ */
