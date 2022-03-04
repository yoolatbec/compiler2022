/*
 * state_machine.h
 *
 *  Created on: 2022年2月26日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_STATUS_MACHINE_H_
#define INCLUDE_MODULES_LEXICAL_STATUS_MACHINE_H_

#include <errcode.h>
#include <modules/lexical/acceptance_func.h>
#include <reserved_word.h>

#define NODE_ATTR_NORMAL (0)
#define NODE_ATTR_START (1 << 0)
#define NODE_ATTR_FINAL (1 << 1)

struct sSTEdge;

typedef struct sSTNode{
	struct sSTEdge* first_edge;
	int node_attr;
} sSTNode;

typedef struct sSTEdge{
	sSTNode* target_node;
	struct sSTEdge* next;
	ACC_FUNC acc_func;
	char* data;
	void (*func)(void*);
} sSTEdge;

int st_add_reserved_word(sSTNode**, sReservedWord*);

int st_merge(sSTNode**, sSTNode*);

int st_new_node(sSTNode**);
int st_new_edge(sSTEdge**);
int st_free_node(sSTNode*);
int st_free_edge(sSTEdge*);

#endif /* INCLUDE_MODULES_LEXICAL_STATUS_MACHINE_H_ */
