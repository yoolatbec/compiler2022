/*
 * status_machine.h
 *
 *  Created on: 2022年2月26日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_STATUS_MACHINE_H_
#define INCLUDE_MODULES_LEXICAL_STATUS_MACHINE_H_

#include <errcode.h>
#include <modules/lexical/acceptance_func.h>
#include <reserved_word.h>

struct sSMEdge;

typedef void (*BY_EFFECT)(void*);

typedef struct sSMNode {
	struct sSMEdge *first_edge;
	int node_attr;
	BY_EFFECT action;
} sSMNode;

typedef struct sSMEdge {
	sSMNode *target_node;
	struct sSMEdge *next;
	ACC_FUNC acc_func;
	char *data;
	BY_EFFECT by_effect;
} sSMEdge;

int sm_add_reserved_word(sSMNode*, sReservedWord*);
int sm_merge(sSMNode*, sSMNode*);

#endif /* INCLUDE_MODULES_LEXICAL_STATUS_MACHINE_H_ */
