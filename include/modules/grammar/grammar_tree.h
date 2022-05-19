/*
 * grammar_tree.h
 *
 *  Created on: 2022年4月7日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_GRAMMAR_GRAMMAR_TREE_H_
#define INCLUDE_MODULES_GRAMMAR_GRAMMAR_TREE_H_

typedef struct sGrammarTreeNode sGrammarTreeNode;

typedef void (*GRAMMAR_TREE_BUILD_FUNC)(sGrammarTreeNode*, void*);

#define GRAMMAR_TREE_BUILD_TYPE_CHILD (0)
#define GRAMMAR_TREE_BUILD_TYPE_PEER (1)

typedef struct sGrammarTreeBuildInfo {
	int build_type;
	int node_type;
	int hashcode;
	void* value0;
	void* value1;
} sGrammarTreeBuildInfo;

sGrammarTreeNode* grammar_tree_node_new();
void grammar_tree_destroy(sGrammarTreeNode*);
void grammar_tree_node_destroy(sGrammarTreeNode*);
void grammar_tree_node_set_hashcode(sGrammarTreeNode*, int);
void grammar_tree_node_set_type(sGrammarTreeNode*, int);
void grammar_tree_node_set_value0(sGrammarTreeNode*, void*);
void grammar_tree_node_set_value1(sGrammarTreeNode*, void*);
void grammar_tree_node_set_parent(sGrammarTreeNode*, sGrammarTreeNode*);
void grammar_tree_node_set_next(sGrammarTreeNode*, sGrammarTreeNode*);
void grammar_tree_node_set_prev(sGrammarTreeNode*, sGrammarTreeNode*);
void grammar_tree_node_set_first_child(sGrammarTreeNode*, sGrammarTreeNode*);

int grammar_tree_node_get_hashcode(sGrammarTreeNode*);
int grammar_tree_node_get_type(sGrammarTreeNode*);
void* grammar_tree_node_get_value0(sGrammarTreeNode*);
void* grammar_tree_node_get_value1(sGrammarTreeNode*);

sGrammarTreeNode* grammar_tree_node_get_parent(sGrammarTreeNode*);
sGrammarTreeNode* grammar_tree_node_get_next(sGrammarTreeNode*);
sGrammarTreeNode* grammar_tree_node_get_prev(sGrammarTreeNode*);
sGrammarTreeNode* grammar_tree_node_get_first_child(sGrammarTreeNode*);

#endif /* INCLUDE_MODULES_GRAMMAR_GRAMMAR_TREE_H_ */
