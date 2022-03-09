/*
 * hash_table.c
 *
 *  Created on: 5 Mar 2022
 *      Author: yoolatbec
 */

#include <utils/hash_table.h>
#include <stdlib.h>

#define FALSE (0)
#define TRUE (!FALSE)

#define HASH_TABLE_NODE_BRANCH_COUNT (17)
#define HASH_TABLE_NODE_LEAF_MARK (1)
#define HASH_TABLE_NEW_NODE_BRANCH_COUNT (9)
#define HASH_TABLE_NODE_GET_PARENT(node) ((sHashTableNode*)((long)node->parent & ~HASH_TABLE_NODE_LEAF_MARK))

sHashTableNode* hash_table_merge(sHashTableNode*, sHashTableNode*);
int hash_table_right_rotate(sHashTableNode*);
int hash_table_left_rotate(sHashTableNode*);
sHashTableNode* hash_table_split(sHashTableNode*);

sHashTableNode* hash_table_leaf_put(sHashTableNode*, int, void*);
sHashTableNode* hash_table_internal_node_put(sHashTableNode*, sHashTableNode*);

int hash_table_has_too_few_branches(sHashTableNode*);
int hash_table_has_too_many_branches(sHashTableNode*);
int hash_table_is_leaf(sHashTableNode*);
void hash_table_make_leaf(sHashTableNode*);

struct sHashTableNode {
	sHashTableNode *parent;
	int branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
	void *branches[HASH_TABLE_NODE_BRANCH_COUNT + 1];
};

typedef struct sHashTableEnd {
	int key;
	sLinkedListNode *values;
} sHashTableEnd;

int hash_table_has_too_few_branches(sHashTableNode *node) {
	return node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1]
		< (HASH_TABLE_NODE_BRANCH_COUNT / 2);
}

int hash_table_has_too_many_branches(sHashTableNode *node) {
	return node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1]
		> HASH_TABLE_NODE_BRANCH_COUNT;
}

int hash_table_is_leaf(sHashTableNode *node) {
	return (long)(node->parent) & HASH_TABLE_NODE_LEAF_MARK != 0;
}

void hash_table_make_leaf(sHashTableNode *node) {
	node->parent = (sHashTableNode*)((long)node->parent
		| HASH_TABLE_NODE_LEAF_MARK);
}

sHashTableNode* hash_table_put(sHashTableNode *root, int key, void *value) {
	if (root == NULL) {
		root = (sHashTableNode*)malloc(sizeof(sHashTableNode));
		root->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] = 0;
		root->parent = NULL & HASH_TABLE_NODE_LEAF_MARK;
	}

	sHashTableNode *current = root;
	while (!hash_table_is_leaf(current)) {
		int branch = 0;
		for (; branch < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1];
			++branch) {
			if (key < current->branch_tag[branch]) {
				break;
			}
		}

		current = (sHashTableNode*)current->branches[branch];
	}

	current = hash_table_leaf_put(current, key, value);

	while (current != NULL && HASH_TABLE_NODE_GET_PARENT(current) != NULL) {
		current = hash_table_internal_node_put(
			HASH_TABLE_NODE_GET_PARENT(current), current);
	}

	if (current != NULL) {
		sHashTableNode *new_root = (sHashTableNode*)malloc(
			sizeof(sHashTableNode));
		new_root->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] = 2;
		new_root->branch_tag[0] =
			current->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT];
		new_root->branches[0] = root;
		new_root->branches = current;
		new_root->parent = NULL;

		root->parent = new_root;
		if (hash_table_is_leaf(current)) {
			hash_table_make_leaf(root);
		}

		current->parent = root->parent;

		return new_root;
	}

	return root;
}

sHashTableNode* hash_table_internal_node_put(sHashTableNode *node,
	sHashTableNode *branch) {
	int tag = branch->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT];
	int index = 0;
	for (; index < node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1];
		index++) {
		if (tag < node->branch_tag[index]) {
			break;
		}
	}

	int i = node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1];
	while (i > index) {
		node->branches[i] = node->branches[--i];
		node->branch_tag[i] = node->branch_tag[i - 1];
	}

	node->branch_tag[index] = tag;
	node->branches[index + 1] = branch;

	++node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1];

	if (hash_table_has_too_many_branches(node)) {
		return hash_table_split(node);
	}

	return NULL;
}

sHashTableNode* hash_table_leaf_put(sHashTableNode *leaf, int key, void *value) {
	if (leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] == 0) {
		sHashTableEnd *end = (sHashTableEnd*)malloc(sizeof(sHashTableEnd));
		end->key = key;
		end->values = linked_list_append(NULL, value);
		leaf->branches[0] = end;
		leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] = 1;
		return NULL;
	}

	int branch = 0;
	for (; branch < leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] - 1;
		branch++) {
		if (key < leaf->branch_tag[branch]) {
			break;
		}
	}

	sHashTableEnd *end = leaf->branches[branch];
	if (key == end->key) {
		sHashTableEnd *end = (sHashTableEnd*)leaf->branches[branch + 1];
		end->values = linked_list_append(end->values, value);
		return NULL;
	}

	int b = leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1];
	while (b - 1 > branch) {
		leaf->branches[b] = leaf->branches[--b];
		leaf->branch_tag[b] = leaf->branch_tag[b - 1];
	}

	leaf->branch_tag[branch] = key;
	sHashTableEnd *end = (sHashTableEnd*)malloc(sizeof(sHashTableEnd));
	end->key = key;
	end->values = linked_list_append(NULL, value);
	leaf->branches[branch + 1] = end;

	leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1]++;

	if (hash_table_has_too_many_branches(leaf)) {
		return hash_table_split(leaf);
	}

	return NULL;
}

sHashTableNode* hash_table_split(sHashTableNode *node) {
	sHashTableNode *new_node = (sHashTableNode*)malloc(sizeof(sHashTableNode));
	new_node->parent = node->parent;

	new_node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] =
	HASH_TABLE_NEW_NODE_BRANCH_COUNT;
	node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] =
	HASH_TABLE_NEW_NODE_BRANCH_COUNT;

	new_node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT] =
		node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT];
	for (int i = 0; i < HASH_TABLE_NEW_NODE_BRANCH_COUNT; i++) {
		new_node->branches[i] = node->branches[HASH_TABLE_NEW_NODE_BRANCH_COUNT
			+ i];
		node->branches[HASH_TABLE_NEW_NODE_BRANCH_COUNT + i] = NULL;

		if (i == 0) {
			continue;
		}

		new_node->branch_tag[i - 1] =
			node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT + i];
	}

	return new_node;
}

int hash_table_contains(sHashTableNode *root, int key, void *value) {
	sLinkedListNode *list = hash_table_get_values(root, key);

	return linked_list_contains(list, value);
}

sLinkedListNode* hash_table_get_values(sHashTableNode *root, int key) {
	if (root == NULL) {
		return NULL;
	}

	sHashTableNode *current = root;
	while (!hash_table_is_leaf(current)) {
		int index = 0;
		for (;
			index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] - 1;
			++index) {
			if (key < current->branches[index]) {
				break;
			}
		}

		current = current->branches[index];
	}

	int index = 0;
	for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] - 1;
		++index) {
		if (key < current->branches[index]) {
			break;
		}
	}

	sHashTableEnd *end = (sHashTableEnd*)current->branches[index];
	if (end->key != key) {
		return NULL;
	}

	return end->values;
}

int hash_table_contains_key(sHashTableNode *root, int key) {
	return hash_table_get_values(root, key) != NULL;
}

sHashTableNode* hash_table_remove(sHashTableNode *root, int key, void *value) {
	if (root == NULL) {
		return NULL;
	}

	sHashTableNode *current = root;
	while (!hash_table_is_leaf(current)) {
		int index = 0;
		for (;
			index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] - 1;
			index++) {
			if (current->branch_tag[index] > key) {
				break;
			}
		}
		current = (sHashTableNode*)current->branches[index];
	}

	int index = 0;
	for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT - 1] - 1;
		index++) {
		if (current->branch_tag[index] > key) {
			break;
		}
	}

	sHashTableEnd *end = (sHashTableEnd*)current->branches[index];

	if(end->key != key){
		return  root;
	}

	end->values = linked_list_remove(end->values, value);
	if(end->values == NULL){

	}
}

sHashTableNode* hash_table_remove_key(sHashTableNode *root, int key) {

}
