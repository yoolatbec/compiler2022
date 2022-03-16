/*
 * main.c
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */
#define DEBUG

//#include <utils/hash_table.h>
#include <utils/linked_list.h>
#include <stdlib.h>
#include <stdio.h>
#include <modules/lexical/sm_util_func.h>

int main() {

	sSMNode *start_node = (sSMNode*)malloc(sizeof(sSMNode));
	sm_build_input_src_end_path(start_node);
	sm_build_identifier_acc_path(start_node);
	sm_build_integer_acc_path(start_node);
	sm_build_char_acc_path(start_node);
	sm_build_string_acc_path(start_node);
	sm_build_blank_ignore_path(start_node);
	sm_build_comment_ignore_path(start_node);
	int i = 0;
	while (reserved_words[i] != NULL) {
		sm_add_reserved_word(start_node, reserved_words[i]);
		++i;
	}

	char *str = "int a = 100;";
	sLinkedListNode *status = NULL;
	sLinkedListNode *last_status = NULL;
	int cursor = 0;
	sSMNode *current_status = start_node;
	last_status = linked_list_append(NULL, current_status);
	sLinkedListNode *terminators = NULL;
	int should_stop = 0;
	while (!should_stop) {
		while (last_status != NULL) {
			sSMNode *node = linked_list_first(last_status);
			if (node->node_attr != 0) {
				if (node->node_attr == INPUT_SRC_END) {
					should_stop = 1;
				}
				terminators = linked_list_append(terminators, node);
			}

			sSMEdge *edge = node->first_edge;
			while (edge != NULL) {
				if (edge->acc_func(str[cursor], edge->data)) {
					status = linked_list_append(status, edge->target_node);
				}

				edge = edge->next;
			}

			last_status = linked_list_remove_first(last_status);
		}

		if (status == NULL) {
			sSMNode *s = (sSMNode*)linked_list_first(terminators);
			printf("%d\n", s->node_attr);
			last_status = linked_list_append(last_status, start_node);
		} else {
			last_status = status;
			status = NULL;
			cursor++;
		}
		terminators = linked_list_clear(terminators);

	}

	return 0;
}
