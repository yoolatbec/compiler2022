/*
 * linked_list.h
 *
 *  Created on: 5 Mar 2022
 *      Author: yoolatbec
 */

#ifndef INCLUDE_UTILS_LINKED_LIST_H_
#define INCLUDE_UTILS_LINKED_LIST_H_

#include <stdlib.h>

typedef struct sLinkedListNode sLinkedListNode;

sLinkedListNode* linked_list_append(sLinkedListNode*, void*);
sLinkedListNode* linked_list_prepend(sLinkedListNode*, void*);
sLinkedListNode* linked_list_insert(sLinkedListNode*, void*, size_t);
sLinkedListNode* linked_list_remove_first(sLinkedListNode*);
sLinkedListNode* linked_list_remove_last(sLinkedListNode*);
sLinkedListNode* linked_list_remove(sLinkedListNode*, void*);
sLinkedListNode* linked_list_remove_nth(sLinkedListNode*, size_t);
void* linked_list_first(sLinkedListNode*);
void* linked_list_last(sLinkedListNode*);
void* linked_list_nth(sLinkedListNode*, size_t);
size_t linked_list_size(sLinkedListNode*);
sLinkedListNode* linked_list_clear(sLinkedListNode*);
int linked_list_contains(sLinkedListNode*, void*);

#endif /* INCLUDE_UTILS_LINKED_LIST_H_ */
