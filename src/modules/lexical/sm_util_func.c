/*
 * sm_util_func.c
 *
 *  Created on: 6 Mar 2022
 *      Author: yoolatbec
 */

#include <modules/lexical/sm_util_func.h>
#include <stdlib.h>

/*
 * identifier构成：
 * [a-zA-Z_][0-9a-zA-Z_]*
 */
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
	edge->by_effect = append_to_buffer_by_func;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = PRIM_ID_IDENTIFIER;
	node->action = identifier_primitive_by_func;

	edge->acc_func = identifier_char_acc_func;
	edge->data = NULL;
	edge->next = NULL;
	edge->by_effect = append_to_buffer_by_func;

	edge->target_node = node;

	return SUCCESS;
}

/*
 * 十进制数字构成：
 * [1-9][0-9]*
 */
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
	node->action = integer_primitive_by_func;

	edge->acc_func = nozero_number_char_acc_func;
	edge->by_effect = append_to_buffer_by_func;
	edge->data = NULL;
	edge->next = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = number_char_acc_func;
	edge->by_effect = append_to_buffer_by_func;
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

/*
 * 八进制数字构成：
 * 0[0-7]*
 */
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
	node->action = octal_integer_primitive_by_func;
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '0';
	edge->next = NULL;
	edge->target_node = node;
	edge->by_effect = append_to_buffer_by_func;

	sSMNode *n = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge->acc_func = nozero_octal_number_char_acc_func;
	edge->data = NULL;
	node->first_edge = edge;
	edge->by_effect = append_to_buffer_by_func;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;
	node->node_attr = PRIM_ID_OCTAL_INTEGER;
	node->action = octal_integer_primitive_by_func;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	edge->acc_func = octal_number_char_acc_func;
	edge->data = NULL;
	edge->target_node = node;
	edge->by_effect = append_to_buffer_by_func;

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

/*
 * 十六进制数字构成：
 * (0x|0X)[0-9a-fA-F]+
 */
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

/*
 * 二进制数字构成：
 * (0b|0B)(0|1)+
 */
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

/*
 * 字符串构成：
 * " 除换行外任何字符 "
 */
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
	edge->by_effect = NULL;
	node->action = NULL;

	edge->next = (sSMEdge*) malloc(sizeof(sSMEdge));
	edge = edge->next;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\"';
	edge->target_node = node;
	node->action = NULL;

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

/*
 * 字符构成：
 * ' 字符 '
 */
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
	edge->by_effect = NULL;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->target_node = node;
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '\'';
	edge->by_effect = NULL;
	edge->next = NULL;

	node->first_edge = NULL;
	node->node_attr = PRIM_ID_CHAR;
	node->action = NULL;

	return SUCCESS;
}

/*
 * 空白符：
 * \n | \t | \s
 */
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

/*
 * 注释构成：
 * \/ \/ 任何字符 \n
 */
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
	edge->data = (char*) '/';
	edge->next = NULL;
	edge->by_effect = NULL;
	edge->target_node = node;

	edge = (sSMEdge*) malloc(sizeof(sSMEdge));
	node->first_edge = edge;
	node->node_attr = 0;

	node = (sSMNode*) malloc(sizeof(sSMNode));
	edge->acc_func = single_char_acc_func;
	edge->data = (char*) '/';
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
