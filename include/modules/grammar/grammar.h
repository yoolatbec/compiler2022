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

typedef struct sGrammar sGrammar;
typedef struct sGrammarBody sGrammarBody;
typedef struct sGrammarNode sGrammarNode;

sGrammarNode* grammar_node_new(int, void*);
sGrammarNode* grammar_node_get_next(sGrammarNode*);
int grammar_node_get_type(sGrammarNode*);
void* grammar_node_get_value(sGrammarNode*);

sGrammarBody* grammar_body_new();
void grammar_body_add_by_func(sGrammarBody*, void(*)());
void grammar_body_destroy(sGrammarBody*);
void grammar_body_append(sGrammarBody*, sGrammarNode*);
sGrammarBody* grammar_body_get_next(sGrammarBody*);
sGrammarNode* grammar_body_get_first_node(sGrammarBody*);
void grammar_body_by_func(sGrammarBody*);
sLinkedListNode* grammar_body_get_firsts(sGrammarBody*);

sGrammar* grammar_new(const char*);
void grammar_destroy(sGrammar*);
void grammar_add(sGrammar*, sGrammarBody*);
sGrammarBody* grammar_get_first_body(sGrammar*);

#endif /* INCLUDE_MODULES_GRAMMAR_GRAMMAR_H_ */
