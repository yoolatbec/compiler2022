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
#include <modules/lexical/by_effect_func.h>
#include <modules/grammar/grammar_tree.h>

struct sSMEdge;

/*
 * 表示有限状态机中节点的数据结构
 */
typedef struct sSMNode {
	struct sSMEdge *first_edge;  //一条离开该节点的边
	int node_attr;  //节点属性（非0表示终止节点，对应的值表示对应的符号类型）
	PRIMITIVE_BY_FUNC action;  //如果这是一个终止节点，在该节点终止时的动作
	GRAMMAR_TREE_BUILD_FUNC build;  //暂未使用
} sSMNode;

/*
 * 表示有限状态机中边的结构
 */
typedef struct sSMEdge {
	sSMNode *target_node;  //目标节点
	struct sSMEdge *next;  //离开节点相同，目标节点不同的下一条边
	ACC_FUNC acc_func;  //接受函数
	char *data;  //接受函数参数
	EDGE_BY_FUNC by_effect;  //从该边跳转时的动作
} sSMEdge;

/*
 * 用于根据保留字构建有限状态机
 */
int sm_add_reserved_word(sSMNode*, const sReservedWord*);

/*
 * 用于合并有限状态机，未使用
 */
int sm_merge(sSMNode*, sSMNode*);

#endif /* INCLUDE_MODULES_LEXICAL_STATUS_MACHINE_H_ */
