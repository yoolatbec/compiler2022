/*
 * grammar_tree.c
 *
 *  Created on: 2022年4月7日
 *      Author: yoolatbec
 */

#include <modules/grammar/grammar_tree.h>
#include <stdlib.h>

struct sGrammarTreeNode {
	int hashcode;
	int type;
	void *value0;
	void *value1;

	sGrammarTreeNode *parent;
	sGrammarTreeNode *next;
	sGrammarTreeNode *prev;
	sGrammarTreeNode *first_child;
};

void grammar_tree_destroy0(sGrammarTreeNode*);

sGrammarTreeNode* grammar_tree_node_new() {
	sGrammarTreeNode *node = (sGrammarTreeNode*) malloc(
			sizeof(sGrammarTreeNode));
	node->hashcode = 0;
	node->type = 0;
	node->first_child = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->parent = NULL;
	node->value0 = NULL;
	node->value1 = NULL;

	return node;
}

void grammar_tree_node_destroy(sGrammarTreeNode *node) {
	free(node);
}

void grammar_tree_destroy(sGrammarTreeNode *root) {
	if (root->parent != NULL && root->parent->first_child == root) {
		root->parent->first_child = root->next;
	}

	if (root->next != NULL) {
		root->next->prev = root->prev;
	}

	if (root->prev != NULL) {
		root->prev->next = root->next;
	}

	grammar_tree_destroy(root->first_child);
	grammar_tree_node_destroy(root);
}

void grammar_tree_destroy0(sGrammarTreeNode *root) {
	if (root == NULL) {
		return;
	}

	if (root->first_child != NULL) {
		grammar_tree_destroy0(root->first_child);
	}

	if (root->next != NULL) {
		grammar_tree_destroy0(root->next);
	}

	grammar_tree_node_destroy(root);
}

void grammar_tree_node_set_hashcode(sGrammarTreeNode *node, int hashcode) {
	node->hashcode = hashcode;
}

void grammar_tree_node_set_type(sGrammarTreeNode *node, int type) {
	node->type = type;
}

void grammar_tree_node_set_value0(sGrammarTreeNode *node, void *value0) {
	node->value0 = value0;
}

void grammar_tree_node_set_value1(sGrammarTreeNode *node, void *value1) {
	node->value1 = value1;
}

void grammar_tree_node_set_parent(sGrammarTreeNode *node,
		sGrammarTreeNode *parent) {
	node->parent = parent;
}

void grammar_tree_node_set_next(sGrammarTreeNode *node, sGrammarTreeNode *next) {
	node->next = next;
}

void grammar_tree_node_set_prev(sGrammarTreeNode *node, sGrammarTreeNode *prev) {
	node->prev = prev;
}

void grammar_tree_node_set_first_child(sGrammarTreeNode *node,
		sGrammarTreeNode *child) {
	node->first_child = child;
}

int grammar_tree_node_get_hashcode(sGrammarTreeNode *node) {
	return node->hashcode;
}

int grammar_tree_node_get_type(sGrammarTreeNode *node) {
	return node->type;
}

void* grammar_tree_node_get_value0(sGrammarTreeNode *node) {
	return node->value0;
}

void* grammar_tree_node_get_value1(sGrammarTreeNode *node) {
	return node->value1;
}

sGrammarTreeNode* grammar_tree_node_get_parent(sGrammarTreeNode *node) {
	return node->parent;
}

sGrammarTreeNode* grammar_tree_node_get_next(sGrammarTreeNode *node) {
	return node->prev;
}

sGrammarTreeNode* grammar_tree_node_get_prev(sGrammarTreeNode *node) {
	return node->prev;
}

sGrammarTreeNode* grammar_tree_node_get_first_child(sGrammarTreeNode *node) {
	return node->first_child;
}
