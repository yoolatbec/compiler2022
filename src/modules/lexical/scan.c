/*
 * scan.c
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#include <modules/lexical/scan.h>
#include <modules/lexical/sm_util_func.h>

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

struct sScanStatus {
	sLinkedListNode *prev_status;
	size_t line;
	size_t column;
};

int scan(sBuffer *input_buffer, sSMNode *sm_root, sLinkedListNode **output,
		sLinkedListNode **primitive_values, sScanStatus *scan_status) {
	char *str = (char*) buffer_read(input_buffer, 0);

	sBuffer *value_buffer = buffer_new(4096);
	*primitive_values = linked_list_append(NULL, value_buffer);

	sLinkedListNode *current_status = NULL;
	sLinkedListNode *prev_status = NULL;
	int cursor = 0;
	sSMNode *current_node = sm_root;
	prev_status = linked_list_append(NULL, current_node);
	sLinkedListNode *terminators = NULL;
	int should_stop = FALSE;
	while (!should_stop) {
		while (prev_status != NULL) {
			sSMNode *node = linked_list_first(prev_status);
			if (node->node_attr != 0) {
				if (node->node_attr == INPUT_SRC_END) {
					should_stop = TRUE;
				}
				terminators = linked_list_append(terminators, node);
			}

			sSMEdge *edge = node->first_edge;
			while (edge != NULL) {
				if (edge->acc_func(str[cursor], edge->data)) {
					current_status = linked_list_append(current_status,
							edge->target_node);
				}

				edge = edge->next;
			}

			prev_status = linked_list_remove_first(prev_status);
		}

		if (current_status == NULL) {
			if (terminators == NULL && !should_stop) {
				//should throw an exception
			}

			sSMNode *s = (sSMNode*) linked_list_first(terminators);
			if (s->node_attr != PRIM_ID_BLANK_IGNORE) {
				sPrimitive *primitive = primitive_new_with_type(s->node_attr);
				*output = linked_list_append(*output, primitive);
			}

			prev_status = linked_list_append(prev_status, sm_root);
		} else {
			prev_status = current_status;
			current_status = NULL;
			cursor++;
		}

		terminators = linked_list_clear(terminators);
	}

	return SUCCESS;
}
