/*
 * hash_table.h
 *
 *  Created on: 5 Mar 2022
 *      Author: yoolatbec
 */

#ifndef INCLUDE_UTILS_HASH_TABLE_H_
#define INCLUDE_UTILS_HASH_TABLE_H_

#include <utils/linked_list.h>

typedef struct sHashTableNode sHashTableNode;

sHashTableNode* hash_table_put(sHashTableNode*, int, void*);
sHashTableNode* hash_table_remove(sHashTableNode*, int, void*);
sHashTableNode* hash_table_remove_key(sHashTableNode*, int);
sLinkedListNode* hash_table_get_values(sHashTableNode*, int);
int hash_table_contains(sHashTableNode*, int, void*);
int hash_table_contains_key(sHashTableNode*, int);
sHashTableNode* hash_table_clear(sHashTableNode*);

#ifdef DEBUG

void hash_table_test(sHashTableNode*);

#endif

#endif /* INCLUDE_UTILS_HASH_TABLE_H_ */
