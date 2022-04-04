/*
 * sm_util_func.c
 *
 *  Created on: 6 Mar 2022
 *      Author: yoolatbec
 */

#include <modules/lexical/sm_util_func.h>
#include <stdlib.h>

int sm_build_identifier_acc_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = head->first_edge;
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = identifier_head_char_acc_func;
	edge->next = NULL;
	edge->data = NULL;
	edge->target_node = node;
	edge->by_effect = identifier_by_effect_func;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = PRIM_ID_IDENTIFIER;
	node->action = buffer_write_back_by_effect_func;

	edge->acc_func = identifier_char_acc_func;
	edge->data = NULL;
	edge->next = NULL;
	edge->by_effect = identifier_by_effect_func;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;

	node->node_attr = PRIM_ID_IDENTIFIER;
	node->action = buffer_write_back_by_effect_func;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = identifier_char_acc_func;
	edge->next = NULL;
	edge->data = NULL;
	edge->target_node = node;
	edge->by_effect = identifier_by_effect_func;

	node->first_edge = edge;

	return SUCCESS;
}

int sm_build_integer_acc_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = head->first_edge;
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = PRIM_ID_INTEGER;

	edge->acc_func = nozero_number_char_acc_func;
	edge->data = NULL;
	edge->next = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = number_char_acc_func;
	edge->data = NULL;
	edge->target_node = node;
	node->first_edge = edge;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";

	node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = PRIM_ID_LONG;
	edge->target_node = node;

	node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge->acc_func = given_char_acc_func;
	node->first_edge->data = "uU";
	node->first_edge->next = NULL;
	node->first_edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));

	node = node->first_edge->target_node;
	node->first_edge = NULL;
	node->node_attr = PRIM_ID_ULONG;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	edge->next = NULL;
	edge->acc_func = given_char_acc_func;
	edge->data = "uU";
	edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node->node_attr = PRIM_ID_UINT;

	edge->target_node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->target_node->first_edge;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";
	edge->target_node = node;
	edge->next = NULL;

	return SUCCESS;
}

int sm_build_octal_integer_acc_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = head->first_edge;
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = PRIM_ID_OCTAL_INTEGER;
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '0';
	edge->next = NULL;
	edge->target_node = node;

	sSMNode *n = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = nozero_octal_number_char_acc_func;
	edge->data = NULL;
	node->first_edge = edge;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;
	node->node_attr = PRIM_ID_OCTAL_INTEGER;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	edge->acc_func = octal_number_char_acc_func;
	edge->data = NULL;
	edge->target_node = node;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";

	sSMEdge *e = edge;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = PRIM_ID_OCTAL_LONG;
	edge->target_node = node;

	node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge->acc_func = given_char_acc_func;
	node->first_edge->data = "uU";
	node->first_edge->next = NULL;
	node->first_edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));

	node = node->first_edge->target_node;
	node->first_edge = NULL;
	node->node_attr = PRIM_ID_OCTAL_ULONG;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	edge->next = NULL;
	edge->acc_func = given_char_acc_func;
	edge->data = "uU";
	edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node->node_attr = PRIM_ID_OCTAL_UINT;

	edge->target_node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->target_node->first_edge;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";
	edge->target_node = node;
	edge->next = NULL;

	edge = n->first_edge;
	while (edge->next != NULL) {
		edge = edge->next;
	}

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '0';
	edge->next = e;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = PRIM_ID_OCTAL_INTEGER;

	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '0';
	edge->target_node = node;
	edge->next = e;

	return SUCCESS;
}

int sm_build_hexadecimal_integer_acc_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = head->first_edge;
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '0';
	edge->next = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = 0;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = given_char_acc_func;
	edge->data = "xX";
	edge->next = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = 0;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = hexadecimal_number_char_acc_func;
	edge->data = NULL;
	edge->next = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = hexadecimal_number_char_acc_func;
	edge->data = NULL;
	edge->target_node = node;
	node->first_edge = edge;
	node->node_attr = PRIM_ID_HEXADECIMAL_INTEGER;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";

	node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = PRIM_ID_HEXADECIMAL_LONG;
	edge->target_node = node;

	node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge->acc_func = given_char_acc_func;
	node->first_edge->data = "uU";
	node->first_edge->next = NULL;
	node->first_edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));

	node = node->first_edge->target_node;
	node->first_edge = NULL;
	node->node_attr = PRIM_ID_HEXADECIMAL_ULONG;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	edge->next = NULL;
	edge->acc_func = given_char_acc_func;
	edge->data = "uU";
	edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node->node_attr = PRIM_ID_HEXADECIMAL_UINT;

	edge->target_node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->target_node->first_edge;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";
	edge->target_node = node;
	edge->next = NULL;

	return SUCCESS;
}

int sm_build_binary_integer_acc_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = head->first_edge;
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	}

	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '0';
	edge->next = NULL;

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->node_attr = 0;
	node->first_edge = edge;

	edge->acc_func = given_char_acc_func;
	edge->data = "bB";
	edge->next = NULL;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = binary_number_char_acc_func;
	edge->data = NULL;
	edge->next = NULL;
	node->first_edge = edge;
	node->node_attr = 0;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = PRIM_ID_BINARY_INTEGER;

	edge->acc_func = binary_number_char_acc_func;
	edge->data = NULL;
	edge->target_node = node;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";

	node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = PRIM_ID_BINARY_LONG;
	edge->target_node = node;

	node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge->acc_func = given_char_acc_func;
	node->first_edge->data = "uU";
	node->first_edge->next = NULL;
	node->first_edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));

	node = node->first_edge->target_node;
	node->first_edge = NULL;
	node->node_attr = PRIM_ID_BINARY_ULONG;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	edge->next = NULL;
	edge->acc_func = given_char_acc_func;
	edge->data = "uU";
	edge->target_node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node->node_attr = PRIM_ID_BINARY_UINT;

	edge->target_node->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->target_node->first_edge;
	edge->acc_func = given_char_acc_func;
	edge->data = "lL";
	edge->target_node = node;
	edge->next = NULL;

	return SUCCESS;
}

int sm_build_string_acc_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = head->first_edge;
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = 0;
	node->action = NULL;

	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\"';
	edge->next = NULL;
	edge->target_node = node;
	edge->by_effect = NULL;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = 0;

	sSMNode *n = node;

	edge->acc_func = any_char_acc_func;
	edge->data = "\\\"";
	edge->target_node = node;
	edge->by_effect = string_by_effect_func;
	node->action = NULL;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\"';
	edge->target_node = node;
	node->action = buffer_write_back_by_effect_func;

	node->first_edge = NULL;
	node->node_attr = PRIM_ID_STRING;

	node = (sSMNode*) malloc(sizeof(sSMNode));

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\\';
	edge->next = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->node_attr = 0;
	node->first_edge = edge;

	edge->acc_func = any_char_acc_func;
	edge->data = NULL;
	edge->next = NULL;
	edge->target_node = n;

	return SUCCESS;
}

//int sm_build_float_acc_path(sSMNode *head) {
//	if(head == NULL){
//		return INVALID_ARGUMENT;
//	}
//}

int sm_build_char_acc_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\'';
	edge->by_effect = NULL;
	edge->next = NULL;
	edge->target_node = node;
	edge->by_effect = NULL;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->node_attr = 0;
	node->first_edge = edge;
	node->action = NULL;

	edge->acc_func = any_char_acc_func;
	edge->data = "\'";
	edge->target_node = node;
	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;
	edge->by_effect = char_by_effect_func;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\'';
	edge->by_effect = NULL;
	edge->next = NULL;

	node->first_edge = NULL;
	node->node_attr = PRIM_ID_CHAR;
	node->action = buffer_write_back_by_effect_func;

	return SUCCESS;
}

int sm_build_blank_ignore_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	node->node_attr = PRIM_ID_BLANK_IGNORE;

	edge->acc_func = blank_char_acc_func;
	edge->next = NULL;
	edge->data = NULL;
	edge->by_effect = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = blank_char_acc_func;
	edge->next = NULL;
	edge->data = NULL;
	edge->by_effect = NULL;
	edge->target_node = node;
	node->first_edge = edge;

	return SUCCESS;
}

int sm_build_comment_ignore_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = head->first_edge;
	if (edge == NULL) {
		head->first_edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	} else {
		while (edge->next != NULL) {
			edge = edge->next;
		}

		edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
		edge = edge->next;
	}

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\\';
	edge->next = NULL;
	edge->by_effect = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = 0;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\\';
	edge->next = NULL;
	edge->by_effect = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = 0;

	edge->acc_func = any_char_acc_func;
	edge->data = "\n";
	edge->by_effect = NULL;
	edge->target_node = node;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	node->first_edge = NULL;
	node->node_attr = PRIM_ID_BLANK_IGNORE;

	edge->target_node = node;
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\n';
	edge->by_effect = NULL;
	edge->next = NULL;

	return SUCCESS;
}

int sm_build_input_src_end_path(sSMNode *head) {
	if (head == NULL) {
		return INVALID_ARGUMENT;
	}

	sSMEdge *edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\0';
	edge->next = head->first_edge;
	head->first_edge = edge;

	sSMNode *node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;
	node->first_edge = NULL;
	node->node_attr = INPUT_SRC_END;

	return SUCCESS;
}
