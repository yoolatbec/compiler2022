/*
 * st_utils.c
 *
 *  Created on: 2022年2月27日
 *      Author: yoolatbec
 */

#include <modules/lexical/st_utils.h>
#define NULL (0)

int st_build_string_path(sSMNode** head){
	sm_node_new(head);
	sSMEdge* edge = NULL;
	sSMNode* node = NULL;

	sm_edge_new(&edge);
	(*head)->first_edge = edge;

	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'\"';

	sm_node_new(&node);
	edge->target_node = node;

	sm_edge_new(&edge);
	edge->acc_func = any_char_acc_func;
	edge->target_node = node;
	node->first_edge = edge;

	sm_edge_new(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'\"';
	node->first_edge->next = edge;

	sm_node_new(&node);
	edge->target_node = node;
	node->node_attr = node->node_attr | NODE_ATTR_FINAL;

	return SUCCESS;
}

int st_build_identifier_path(sSMNode** head){
	sm_node_new(head);
	sSMNode* node = NULL;
	sSMEdge* edge = NULL;

	sm_edge_new(&edge);
	edge->acc_func = identifier_char_acc_func;
	(*head)->first_edge = edge;

	sm_node_new(&node);
	edge->target_node = node;
	node->node_attr = node->node_attr | NODE_ATTR_FINAL;

	sm_edge_new(&edge);
	edge->acc_func = identifier_char_acc_func;
	edge->target_node = node;

	return SUCCESS;
}

int st_build_single_line_comment_path(sSMNode** head){
	sm_node_new(head);
	sSMNode* node = NULL;
	sSMEdge* edge = NULL;

	sm_edge_new(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'/';
	(*head)->first_edge = edge;

	sm_node_new(&node);
	edge->target_node = node;

	sm_edge_new(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'/';
	node->first_edge = edge;

	sm_node_new(&node);
	edge->target_node = node;

	sm_edge_new(&edge);
	edge->acc_func = any_char_acc_func;
	edge->target_node = node;
	node->first_edge = edge;

	sm_edge_new(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'\n';
	node->first_edge->next = edge;

	sm_node_new(&node);
	node->node_attr = node->node_attr | NODE_ATTR_FINAL;
	edge->target_node = node;

	return SUCCESS;
}
