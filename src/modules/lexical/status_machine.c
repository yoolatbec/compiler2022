/*
 * status_machine.c
 *
 *  Created on: 2022年2月26日
 *      Author: yoolatbec
 */

#include <modules/lexical/status_machine.h>
#include <stdlib.h>
#include <utils/linked_list.h>

#define FALSE (0)
#define TRUE (!FALSE)

#define ACCEPT_SINGLE_CHAR(edge, c) (edge->acc_func == single_char_acc_func && c == (char)edge->data)
#define ACCEPT_LOWER_CASE_CHAR(edge) (edge->acc_func == lower_case_char_acc_func)
#define ACCEPT_HIGHER_CASE_CHAR(edge) (edge->acc_func == higher_case_char_acc_func)
#define ACCEPT_NUMBER_CHAR(edge) (edge->acc_func == number_char_acc_func)
#define ACCEPT_BLANK_CHAR(edge) (edge->acc_func == blank_char_acc_func)
#define ACCEPT_IDENTIFIER_CHAR(edge) (edge->acc_func == identifier_char_acc_func)
#define ACCEPT_IDENTIFIER_HEAD_CHAR(edge) (edge->acc_func == identifier_head_char_acc_func)
#define ACCEPT_ANY_CHAR(edge) (edge->acc_func == any_char_acc_func)

#define RULE_TREE_NODE_ATTR_ONE_OR_MORE (1 << 0)
#define RULE_TREE_NODE_ATTR_ZERO_OR_MORE (1 << 1)

int sm_add_reserved_word(sSMNode *head, const sReservedWord *kw) {
	if (head == NULL || kw == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMNode *current_node = head;
	int kw_cursor = 0;
	while (1) {
		if (kw->value[kw_cursor] == '\0') {
			if (kw_cursor != 0) {
				current_node->node_attr = kw->id;
			}
			break;
		}

		sSMEdge *current_edge = current_node->first_edge;
		while (current_edge != NULL) {
			if (!ACCEPT_SINGLE_CHAR(current_edge, kw->value[kw_cursor])) {
				current_edge = current_edge->next;
				continue;
			}

			current_node = current_edge->target_node;
			++kw_cursor;

			goto OUTER_END;
		}

		sSMNode *new_node = (sSMNode*)malloc(sizeof(sSMNode));
		sSMEdge *new_edge = (sSMEdge*)malloc(sizeof(sSMEdge));

		new_edge->acc_func = single_char_acc_func;
		new_edge->data = (char*)(kw->value[kw_cursor]);
		new_edge->target_node = new_node;
		new_edge->next = current_node->first_edge;
		new_edge->by_effect = NULL;
		current_node->first_edge = new_edge;

		current_node = new_node;
		new_node->first_edge = NULL;
		new_node->action = NULL;
		new_node->node_attr = 0;
		++kw_cursor;

		OUTER_END:
		;
	}

	return SUCCESS;
}

int sm_merge(sSMNode *head, sSMNode *another_head) {
	if (head == NULL || another_head == NULL) {
		return INVALID_ARGUMENT;
	}

	sLinkedListNode *queue = NULL;
	int visited_mark = 1;

	sSMEdge *current_edge = another_head->first_edge;
	while (current_edge != NULL) {
		queue = linked_list_append(queue, current_edge);
		current_edge = current_edge->next;
	}

	another_head->first_edge = (sSMEdge*)((long)another_head->first_edge
		| visited_mark);
	head->first_edge = (sSMEdge*)((long)head->first_edge | visited_mark);

	while (queue != NULL) {
		current_edge = (sSMEdge*)linked_list_first(queue);

		if (((long)(current_edge->target_node->first_edge) & visited_mark)
			== 0) {
			sSMEdge *e = current_edge->target_node->first_edge;
			while (e != NULL) {
				linked_list_append(queue, e);
				e = e->next;
			}

			current_edge->target_node->first_edge =
				(sSMEdge*)((long)current_edge->target_node->first_edge
					| visited_mark);
		}

		if (current_edge->target_node == another_head) {
			current_edge->target_node = head;
		}

		linked_list_remove_first(queue);
	}

	head->first_edge = (sSMEdge*)((long)head->first_edge & ~visited_mark);

	current_edge = (sSMEdge*)((long)another_head->first_edge & ~visited_mark);
	while (current_edge != NULL) {
		queue = linked_list_append(queue, current_edge);
		current_edge = current_edge->next;
	}

	while (queue != NULL) {
		current_edge = (sSMEdge*)linked_list_first(queue);

		if (((long)current_edge->target_node->first_edge & visited_mark) != 0) {
			current_edge->target_node->first_edge =
				(sSMEdge*)((long)current_edge->target_node->first_edge
					& ~visited_mark);
			sSMEdge *e = current_edge->target_node->first_edge;
			while (e != NULL) {
				linked_list_append(queue, e);
			}
		}

		linked_list_remove_first(queue);
	}

	current_edge = head->first_edge;
	if (current_edge == NULL) {
		current_edge = another_head->first_edge;
	} else {
		while (current_edge->next != NULL) {
			current_edge = current_edge->next;
		}

		current_edge->next = another_head->first_edge;
	}

	free(another_head);

	return SUCCESS;
}

