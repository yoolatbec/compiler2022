/*
 * st_utils.c
 *
 *  Created on: 2022年2月27日
 *      Author: yoolatbec
 */

#include <modules/lexical/st_utils.h>
#define NULL (0)

int st_build_string_path(sSTNode** head){
	st_new_node(head);
	sSTEdge* edge = NULL;
	sSTNode* node = NULL;

	st_new_edge(&edge);
	(*head)->first_edge = edge;

	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'\"';

	st_new_node(&node);
	edge->target_node = node;

	st_new_edge(&edge);
	edge->acc_func = any_char_acc_func;
	edge->target_node = node;
	node->first_edge = edge;

	st_new_edge(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'\"';
	node->first_edge->next = edge;

	st_new_node(&node);
	edge->target_node = node;
	node->node_attr = node->node_attr | NODE_ATTR_FINAL;

	return SUCCESS;
}

int st_build_identifier_path(sSTNode** head){
	st_new_node(head);
	sSTNode* node = NULL;
	sSTEdge* edge = NULL;

	st_new_edge(&edge);
	edge->acc_func = identifier_char_acc_func;
	(*head)->first_edge = edge;

	st_new_node(&node);
	edge->target_node = node;
	node->node_attr = node->node_attr | NODE_ATTR_FINAL;

	st_new_edge(&edge);
	edge->acc_func = identifier_char_acc_func;
	edge->target_node = node;

	return SUCCESS;
}

int st_build_single_line_comment_path(sSTNode** head){
	st_new_node(head);
	sSTNode* node = NULL;
	sSTEdge* edge = NULL;

	st_new_edge(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'/';
	(*head)->first_edge = edge;

	st_new_node(&node);
	edge->target_node = node;

	st_new_edge(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'/';
	node->first_edge = edge;

	st_new_node(&node);
	edge->target_node = node;

	st_new_edge(&edge);
	edge->acc_func = any_char_acc_func;
	edge->target_node = node;
	node->first_edge = edge;

	st_new_edge(&edge);
	edge->acc_func = single_char_acc_func;
	edge->data = (char*)'\n';
	node->first_edge->next = edge;

	st_new_node(&node);
	node->node_attr = node->node_attr | NODE_ATTR_FINAL;
	edge->target_node = node;

	return SUCCESS;
}
