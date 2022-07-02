/*
 * grammar.h
 *
 *  Created on: 2022年4月14日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_GRAMMAR_GRAMMAR_H_
#define INCLUDE_MODULES_GRAMMAR_GRAMMAR_H_

#include <reserved_word.h>
#include <utils/linked_list.h>

#define GRAMMAR_NODE_TYPE_TOKEN (1)
#define GRAMMAR_NODE_TYPE_GRAMMAR_HEAD (2)

/*
 * 表示左部相同的产生式的结构
 */
typedef struct sGrammar sGrammar;

/*
 * 表示一条产生式的结构
 */
typedef struct sGrammarBody sGrammarBody;

/*
 * 表示产生式中的符号节点或动作节点的结构
 * 一个符号节点表示产生式中的一个符号
 * 一个动作节点表示匹配过程中的动作
 */
typedef struct sGrammarNode sGrammarNode;

typedef void (*GRAMMAR_NODE_FUNC)(void*);

sGrammarNode* grammar_node_new(int, void*);
sGrammarNode* grammar_node_get_next(sGrammarNode*);
int grammar_node_is_function_node(sGrammarNode*);  //用于判断一个节点是否为动作节点
int grammar_node_has_function(sGrammarNode*);  //用于判断一个节点是否包含动作
void grammar_node_function(sGrammarNode*, void*);  //执行一个节点的动作
void grammar_node_set_function(sGrammarNode*, GRAMMAR_NODE_FUNC);
int grammar_node_get_type(sGrammarNode*);
void* grammar_node_get_value(sGrammarNode*);

sGrammarBody* grammar_body_new();
void grammar_body_add_by_func(sGrammarBody*, void(*)());
void grammar_body_destroy(sGrammarBody*);
void grammar_body_append(sGrammarBody*, sGrammarNode*);  //将一个节点添加到产生式末尾
sGrammarBody* grammar_body_get_next(sGrammarBody*);  //获得下一条产生式
sGrammarNode* grammar_body_get_first_node(sGrammarBody*);
void grammar_body_by_func(sGrammarBody*);
sLinkedListNode* grammar_body_get_firsts(sGrammarBody*);

sGrammar* grammar_new(const char*);
void grammar_destroy(sGrammar*);
void grammar_add(sGrammar*, sGrammarBody*);  //将一条产生式添加到集合中
sGrammarBody* grammar_get_first_body(sGrammar*);

#endif /* INCLUDE_MODULES_GRAMMAR_GRAMMAR_H_ */
