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

int hash_table_merge(sHashTableNode*, sHashTableNode*);
int hash_table_right_rotate(sHashTableNode*);
int hash_table_left_rotate(sHashTableNode*);
sHashTableNode* hash_table_split(sHashTableNode*);

sHashTableNode* hash_table_leaf_put(sHashTableNode*, int, void*);
sHashTableNode* hash_table_internal_node_put(sHashTableNode*, sHashTableNode*);

inline int hash_table_has_too_few_branches(sHashTableNode*);
inline int hash_table_will_have_too_few_branches(sHashTableNode*);
inline int hash_table_has_too_many_branches(sHashTableNode*);
inline int hash_table_is_leaf(sHashTableNode*);
inline int hash_table_is_root(sHashTableNode*);
void hash_table_make_leaf(sHashTableNode*);

struct sHashTableNode {
	sHashTableNode *parent;
	int branch_tag[HASH_TABLE_NODE_BRANCH_COUNT + 1];
	void *branches[HASH_TABLE_NODE_BRANCH_COUNT + 1];
};

typedef struct sHashTableEnd {
	int key;
	sLinkedListNode *values;
} sHashTableEnd;

int hash_table_has_too_few_branches(sHashTableNode *node) {
	return (!hash_table_is_root(node)
			&& node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]
					< HASH_TABLE_NEW_NODE_BRANCH_COUNT)
			|| (hash_table_is_root(node)
					&& node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] == 1);
}

int hash_table_has_too_many_branches(sHashTableNode *node) {
	return node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]
			> HASH_TABLE_NODE_BRANCH_COUNT;
}

int hash_table_is_leaf(sHashTableNode *node) {
	return ((long) (node->parent) & HASH_TABLE_NODE_LEAF_MARK) != 0;
}

int hash_table_is_root(sHashTableNode *node) {
	return HASH_TABLE_NODE_GET_PARENT(node) == NULL;
}

void hash_table_make_leaf(sHashTableNode *node) {
	node->parent = (sHashTableNode*) ((long) node->parent
			| HASH_TABLE_NODE_LEAF_MARK);
}

sHashTableNode* hash_table_put(sHashTableNode *root, int key, void *value) {
	if (root == NULL) {
		root = (sHashTableNode*) malloc(sizeof(sHashTableNode));
		root->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] = 0;
		root->parent = NULL;
		hash_table_make_leaf(root);
	}

	sHashTableNode *current = root;
	while (!hash_table_is_leaf(current)) {
		int branch = 0;
		for (; branch < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
				++branch) {
			if (key < current->branch_tag[branch]) {
				break;
			}
		}

		current = (sHashTableNode*) current->branches[branch];
	}

	current = hash_table_leaf_put(current, key, value);

	while (current != NULL && !hash_table_is_root(current)) {
		current = hash_table_internal_node_put(
				HASH_TABLE_NODE_GET_PARENT(current), current);
	}

	if (current != NULL && hash_table_is_root(current)) {
		sHashTableNode *new_root = (sHashTableNode*) malloc(
				sizeof(sHashTableNode));
		new_root->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] = 2;
		new_root->branch_tag[0] =
				current->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT];
		new_root->branches[0] = root;
		new_root->branches[1] = (void*) current;
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
	int tag = branch->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1];
	int index = 0;
	for (; index < node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
			index++) {
		if (tag < node->branch_tag[index]) {
			break;
		}
	}

	int i = node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
	for (; i > index + 1; i--) {
		node->branches[i] = node->branches[i - 1];
		node->branch_tag[i - 1] = node->branch_tag[i - 2];
	}

	node->branch_tag[index] = tag;
	node->branches[index + 1] = branch;

	++node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];

	if (hash_table_has_too_many_branches(node)) {
		return hash_table_split(node);
	}

	return NULL;
}

sHashTableNode* hash_table_leaf_put(sHashTableNode *leaf, int key, void *value) {
	if (leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] == 0) {
		sHashTableEnd *end = (sHashTableEnd*) malloc(sizeof(sHashTableEnd));
		end->key = key;
		end->values = linked_list_append(NULL, value);
		leaf->branches[0] = end;
		leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] = 1;
		return NULL;
	}

	int branch = 0;
	for (; branch < leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
			branch++) {
		if (key < leaf->branch_tag[branch]) {
			break;
		}
	}

	sHashTableEnd *end = leaf->branches[branch];
	if (key == end->key) {
		end->values = linked_list_append(end->values, value);
		return NULL;
	}

	int b = leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
	for (; b > branch + 1; --b) {
		leaf->branches[b] = leaf->branches[b - 1];
		leaf->branch_tag[b - 1] = leaf->branch_tag[b - 2];
	}

	leaf->branch_tag[branch] = key;
	end = (sHashTableEnd*) malloc(sizeof(sHashTableEnd));
	end->key = key;
	end->values = linked_list_append(NULL, value);
	leaf->branches[branch + 1] = end;

	++leaf->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];

	if (hash_table_has_too_many_branches(leaf)) {
		return hash_table_split(leaf);
	}

	return NULL;
}

sHashTableNode* hash_table_split(sHashTableNode *node) {
	sHashTableNode *new_node = (sHashTableNode*) malloc(sizeof(sHashTableNode));
	new_node->parent = node->parent;

	new_node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] =
	HASH_TABLE_NEW_NODE_BRANCH_COUNT;
	node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] =
	HASH_TABLE_NEW_NODE_BRANCH_COUNT;

	for (int i = 0; i < HASH_TABLE_NEW_NODE_BRANCH_COUNT; i++) {
		new_node->branches[i] = node->branches[HASH_TABLE_NEW_NODE_BRANCH_COUNT
				+ i];
		node->branches[HASH_TABLE_NEW_NODE_BRANCH_COUNT + i] = NULL;

		new_node->branch_tag[i] =
				node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT + i];
	}

	new_node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1] =
			node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1];

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
		for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
				++index) {
			if (key < current->branch_tag[index]) {
				break;
			}
		}

		current = current->branches[index];
	}

	int index = 0;
	for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
			++index) {
		if (key < current->branch_tag[index]) {
			break;
		}
	}

	sHashTableEnd *end = (sHashTableEnd*) current->branches[index];
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
		for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
				index++) {
			if (current->branch_tag[index] > key) {
				break;
			}
		}
		current = (sHashTableNode*) current->branches[index];
	}

	int index = 0;
	for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
			index++) {
		if (current->branch_tag[index] > key) {
			break;
		}
	}

	sHashTableEnd *end = (sHashTableEnd*) current->branches[index];

	if (end->key != key) {
		return root;
	}

	end->values = linked_list_remove(end->values, value);
	if (end->values == NULL) {
		for (int i = index;
				i < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
				i++) {
			current->branches[i] = current->branches[i + 1];
			if (i == 0) {
				continue;
			}

			current->branch_tag[i - 1] = current->branch_tag[i];
		}

		current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]--;

		while (hash_table_has_too_few_branches(current)
				&& !hash_table_is_root(current)) {
			if (hash_table_left_rotate(current)) {
				break;
			}

			if (hash_table_right_rotate(current)) {
				break;
			}

			sHashTableNode *parent = HASH_TABLE_NODE_GET_PARENT(current);
			hash_table_merge(current, parent);

			current = parent;
		}

		if (hash_table_has_too_few_branches(current)
				&& hash_table_is_root(current)) {
			root = current->branches[0];
			if (hash_table_is_leaf(root)) {
				root->parent = NULL;
				hash_table_make_leaf(root);
			}
			free(current);
		}
	}

	return root;
}

sHashTableNode* hash_table_remove_key(sHashTableNode *root, int key) {
	if (root == NULL) {
		return NULL;
	}

	sHashTableNode *current = root;
	while (!hash_table_is_leaf(current)) {
		int index = 0;
		for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
				index++) {
			if (current->branch_tag[index] > key) {
				break;
			}
		}
		current = (sHashTableNode*) current->branches[index];
	}

	int index = 0;
	for (; index < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
			index++) {
		if (current->branch_tag[index] > key) {
			break;
		}
	}

	sHashTableEnd *end = (sHashTableEnd*) current->branches[index];

	if (end->key != key) {
		return root;
	}

	linked_list_clear(end->values);
	for (int i = index;
			i < current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1; i++) {
		current->branches[i] = current->branches[i + 1];
		if (i == 0) {
			continue;
		}

		current->branch_tag[i - 1] = current->branch_tag[i];
	}

	current->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]--;

	while (hash_table_has_too_few_branches(current)
			&& !hash_table_is_root(current)) {
		if (hash_table_left_rotate(current)) {
			break;
		}

		if (hash_table_right_rotate(current)) {
			break;
		}

		sHashTableNode *parent = HASH_TABLE_NODE_GET_PARENT(current);
		hash_table_merge(current, parent);

		current = parent;
	}

	if (hash_table_has_too_few_branches(current)
			&& hash_table_is_root(current)) {
		root = current->branches[0];
		if (hash_table_is_leaf(root)) {
			root->parent = NULL;
			hash_table_make_leaf(root);
		}
		free(current);
	}

	return root;
}

int hash_table_left_rotate(sHashTableNode *node) {
	sHashTableNode *parent = HASH_TABLE_NODE_GET_PARENT(node);

	if (node
			== parent->branches[parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]
					- 1]) {
		return FALSE;
	}

	int index = 0;
	for (; index < parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1;
			index++) {
		if (parent->branches[index] == node) {
			break;
		}
	}

	++index;
	sHashTableNode *brother = parent->branches[index];
	if (hash_table_will_have_too_few_branches(brother)) {
		return FALSE;
	}

	node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT - 2] =
			parent->branch_tag[index - 1];
	node->branches[HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1] = brother->branches[0];
	parent->branch_tag[index - 1] = brother->branch_tag[0];

	--brother->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];

	for (int i = 0; i < brother->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
			i++) {
		brother->branches[i] = brother->branches[i + 1];
		if (i < brother->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT] - 1) {
			brother->branch_tag[i] = brother->branch_tag[i + 1];
		}
	}

	return TRUE;
}

int hash_table_right_rotate(sHashTableNode *node) {
	sHashTableNode *parent = HASH_TABLE_NODE_GET_PARENT(node);

	if (node == parent->branches[0]) {
		return FALSE;
	}

	int index = 0;
	for (; index < parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]; index++) {
		if (parent->branches[index] == node) {
			break;
		}
	}

	--index;
	sHashTableNode *brother = parent->branches[index];
	if (hash_table_will_have_too_few_branches(brother)) {
		return FALSE;
	}

	int branch = node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
	while (branch > 0) {
		node->branches[branch] = node->branches[branch - 1];
		if (branch > 1) {
			node->branch_tag[branch - 1] = node->branch_tag[branch - 2];
		}

		--branch;
	}

	node->branch_tag[0] = parent->branch_tag[index];

	--brother->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];

	node->branches[0] =
			brother->branches[brother->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]];
	parent->branch_tag[index] =
			brother->branch_tag[brother->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]
					- 1];

	return TRUE;
}

int hash_table_merge(sHashTableNode *node, sHashTableNode *parent) {
	if (node == parent->branches[0]) {
		node->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT - 2] =
				parent->branch_tag[0];
		sHashTableNode *brother = parent->branches[1];
		for (int i = HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1;
				i < 2 * HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1; i++) {
			node->branches[i] = brother->branches[i
					- HASH_TABLE_NEW_NODE_BRANCH_COUNT + 1];
			if (i < 2 * HASH_TABLE_NEW_NODE_BRANCH_COUNT - 2) {
				node->branch_tag[i] = brother->branch_tag[i
						- HASH_TABLE_NEW_NODE_BRANCH_COUNT + 1];
			}
		}

		--parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
		for (int i = 1; i < parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
				i++) {
			parent->branches[i] = parent->branches[i + 1];
			parent->branch_tag[i - 1] = parent->branch_tag[i];
		}

		return TRUE;
	}

	int index = 0;
	for (; index < parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]; index++) {
		if (parent->branches[index] == node) {
			break;
		}
	}

	--index;
	sHashTableNode *brother = parent->branches[index];
	brother->branch_tag[HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1] =
			parent->branch_tag[index];
	for (int i = HASH_TABLE_NEW_NODE_BRANCH_COUNT;
			i < 2 * HASH_TABLE_NEW_NODE_BRANCH_COUNT - 1; i++) {
		brother->branches[i] = node->branches[i
				- HASH_TABLE_NEW_NODE_BRANCH_COUNT];
		if (i < 2 * HASH_TABLE_NEW_NODE_BRANCH_COUNT - 2) {
			brother->branch_tag[i] = node->branch_tag[i
					- HASH_TABLE_NEW_NODE_BRANCH_COUNT];
		}
	}

	--parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
	for (int i = index; i < parent->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
			i++) {
		parent->branch_tag[i] = parent->branch_tag[i + 1];
		parent->branches[i + 1] = parent->branches[i + 2];
	}

	return TRUE;
}

int hash_table_will_have_too_few_branches(sHashTableNode *node) {
	return node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT]
			== HASH_TABLE_NEW_NODE_BRANCH_COUNT;
}

sHashTableNode* hash_table_clear(sHashTableNode *root) {
	if (root == NULL) {
		return NULL;
	}

	sLinkedListNode *list = linked_list_append(NULL, root);
	while (list != NULL) {
		sHashTableNode *node = linked_list_first(list);
		if (hash_table_is_leaf(node)) {
			for (int i = 0; i < node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
					i++) {
				sHashTableEnd *end = (sHashTableEnd*) node->branches[i];
				linked_list_clear(end->values);
				free(end);
			}
		} else {
			for (int i = 0; i < node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
					i++) {
				linked_list_append(list, node->branches[i]);
			}
		}

		linked_list_remove_first(list);
		free(node);
	}

	return NULL;
}

#ifdef DEBUG

void hash_table_test(sHashTableNode *root) {
	sLinkedListNode *list = linked_list_append(NULL, root);
	while (list != NULL) {
		sHashTableNode *node = linked_list_first(list);
		if (hash_table_is_leaf(node)) {
			for (int i = 0; i < node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
					i++) {
				sHashTableEnd *end = (sHashTableEnd*) node->branches[i];
				linked_list_test(end->values);
			}
		} else {
			for (int i = 0; i < node->branch_tag[HASH_TABLE_NODE_BRANCH_COUNT];
					i++) {
				linked_list_append(list, node->branches[i]);
			}
		}

		list = linked_list_remove_first(list);
	}
}

#endif
