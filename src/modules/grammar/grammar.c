/*
 * grammar.c
 *
 *  Created on: 2022年4月14日
 *      Author: yoolatbec
 */

#include <modules/grammar/grammar.h>
#include <stdlib.h>

/*
 * 产生式中的节点，可以是符号或动作
 * 如果一个节点表示终结符号，则type表示对应的类型（见reserved_word.h）
 * 如果一个节点表示非终结符号，则type为0，value指示以该非终结符号为左部的
 * 产生式的集合
 * 如果一个节点为动作节点，则type为0且value为NULL
 */
struct sGrammarNode {
	sGrammarNode *next;  //下一个节点
	int type;
	void *value;
	GRAMMAR_NODE_FUNC func;  //语法分析动作
};

/*
 * 表示一条产生式
 */
struct sGrammarBody {
	sGrammarNode *first_node;  //右部第一个节点
	sGrammarBody *next_peer;  //左部相同的下一条产生式
	void (*by_func)();  //辅助函数
	sLinkedListNode *firsts;  //First集
};

/*
 * 表示左部相同的所有产生式
 */
struct sGrammar {
	sGrammarBody *first_body;  //第一条产生式
	const char *name;  //左部名称
};

sGrammarNode* grammar_node_new(int type, void *value) {
	sGrammarNode *node = (sGrammarNode*) malloc(sizeof(sGrammarNode));

	node->type = type;
	node->value = value;
	node->next = NULL;
	node->func = NULL;

	return node;
}

sGrammarNode* grammar_node_get_next(sGrammarNode *node) {
	return node->next;
}

int grammar_node_is_function_node(sGrammarNode *node) {
	return node->func != NULL && node->type == 0 && node->value == NULL;
}

int grammar_node_has_function(sGrammarNode *node) {
	return node->func != NULL;
}

void grammar_node_function(sGrammarNode *node, void *data) {
	node->func(data);
}

void grammar_node_set_function(sGrammarNode *node, GRAMMAR_NODE_FUNC func) {
	node->func = func;
}

int grammar_node_get_type(sGrammarNode *node) {
	return node->type;
}

void* grammar_node_get_value(sGrammarNode *node) {
	return node->value;
}

sGrammarBody* grammar_body_new() {
	sGrammarBody *body = (sGrammarBody*) malloc(sizeof(sGrammarBody));

	body->first_node = NULL;
	body->next_peer = NULL;

	return body;
}

void grammar_body_destroy(sGrammarBody *body) {
	if (body->first_node == NULL) {
		free(body);
		return;
	}

	sGrammarNode *node = body->first_node;
	while (node->next != NULL) {
		sGrammarNode *n = node->next;
		free(node);
		node = n;
	}

	free(node);
}

void grammar_body_add_by_func(sGrammarBody *body, void (*by_func)()) {
	body->by_func = by_func;
}

/*
 * 用于将一个节点添加到产生式中
 * 在必要时计算First集
 */
void grammar_body_append(sGrammarBody *body, sGrammarNode *node) {
	if (body->first_node == NULL) {
		//如果为第一个节点
		body->first_node = node;
		if (grammar_node_get_type(node) != 0) {
			//如果节点符号为终结符号，将其添加到First集中
			body->firsts = linked_list_append(body->firsts,
					(void*) grammar_node_get_type(node));
		} else {
			//如果节点符号为非终结符号，则添加对应文法的First集中的元素
			sGrammar *grammar = grammar_node_get_value(node);
			if (grammar == NULL) {
				body->firsts = linked_list_append(body->firsts, NULL);
			} else {
				sGrammarBody *b = grammar_get_first_body(grammar);
				while (b != NULL) {
					sLinkedListNode *firsts = grammar_body_get_firsts(b);
					size_t size = linked_list_size(firsts);
					for (int i = 0; i < size; ++i) {
						int type = linked_list_nth(firsts, i);
						if (linked_list_contains(body->firsts, (void*) type)) {
							continue;
						}
						body->firsts = linked_list_append(body->firsts,
								(void*) type);
					}
					b = b->next_peer;
				}
			}
		}
		return;
	}

	sGrammarNode *n = body->first_node;
	while (n->next != NULL) {
		n = n->next;
	}

	n->next = node;
}

sGrammarBody* grammar_body_get_next(sGrammarBody *body) {
	return body->next_peer;
}

sGrammarNode* grammar_body_get_first_node(sGrammarBody *body) {
	return body->first_node;
}

sGrammar* grammar_new(const char *head) {
	sGrammar *grammar = (sGrammar*) malloc(sizeof(sGrammar));
	grammar->name = head;
	grammar->first_body = NULL;

	return grammar;
}

void grammar_body_by_func(sGrammarBody *body) {
	body->by_func();
}

sLinkedListNode* grammar_body_get_firsts(sGrammarBody *body) {
	return body->firsts;
}

void grammar_destroy(sGrammar *grammar) {
	if (grammar->first_body == NULL) {
		free(grammar);
		return;
	}

	sGrammarBody *body = grammar->first_body;
	while (body != NULL) {
		sGrammarBody *b = body->next_peer;
		grammar_body_destroy(body);
		body = b;
	}

	free(grammar);
}

void grammar_add(sGrammar *grammar, sGrammarBody *body) {
	if (grammar->first_body == NULL) {
		grammar->first_body = body;
		return;
	}

	sGrammarBody *b = grammar->first_body;
	while (b->next_peer != NULL) {
		b = b->next_peer;
	}

	b->next_peer = body;
}

sGrammarBody* grammar_get_first_body(sGrammar *grammar) {
	return grammar->first_body;
}
