/*
 * status_machine.c
 *
 *  Created on: 2022年2月26日
 *      Author: yoolatbec
 */

#include <modules/lexical/status_machine.h>
#include <stdlib.h>

#define FALSE (0)
#define TRUE (!FALSE)

#define ACCEPT_SINGLE_CHAR(edge, c) (edge->acc_func == single_char_acc_func && c == (char)edge->data)
#define ACCEPT_LOWER_CASE_CHAR(edge) (edge->acc_func == lower_case_char_acc_func)
#define ACCEPT_HIGHER_CASE_CHAR(edge) (edge->acc_func == higher_case_char_acc_func)
#define ACCEPT_NUMBER_CHAR(edge) (edge->acc_func == number_char_acc_func)
#define ACCEPT_BLANK_CHAR(edge) (edge->acc_func == blank_char_acc_func)
#define ACCEPT_IDENTIFIER_CHAR(edge) (edge->acc_func == identifier_char_acc_func)
#define ACCEPT_ANY_CHAR(edge) (edge->acc_func == any_char_acc_func)

#define RULE_TREE_NODE_ATTR_ONE_OR_MORE (1 << 0)
#define RULE_TREE_NODE_ATTR_ZERO_OR_MORE (1 << 1)

int st_build_new_st(sSTNode**);

int st_append_reserved_word(sSTNode **head, sReservedWord *kw) {
	if (*head == NULL) {
		st_build_new_st(head);
	}

	sSTNode *current_node = *head;
	int kw_cursor = 0;
	while (1) {
		if (kw->value[kw_cursor] == '\0') {
			if (kw_cursor != 0) {
				current_node->node_attr = current_node->node_attr
						| NODE_ATTR_FINAL;
			}
			break;
		}

		sSTEdge *current_edge = current_node->first_edge;
		while (current_edge != NULL) {
			if (!current_edge->acc_func(kw->value[kw_cursor],
					current_edge->data)) {
				current_edge = current_edge->next;
				continue;
			}

			current_node = current_edge->target_node;
			++kw_cursor;

			goto OUTER_END;
		}

		sSTNode *new_node;
		sSTEdge *new_edge;
		st_new_node(&new_node);
		st_new_edge(&new_edge);

		new_edge->acc_func = single_char_acc_func;
		new_edge->data = (char*) (kw->value[kw_cursor]);
		new_edge->target_node = new_node;
		new_edge->next = current_node->first_edge;
		current_node->first_edge = new_edge;

		current_node = new_node;

		OUTER_END: ;
	}

	return SUCCESS;
}
//
//int st_apply_rule(s_st_node **head, s_rule *rule) {
//	if (*head == NULL) {
//		st_build_new_st(head);
//	}
//
//	int escape_flag = FALSE;
//	s_st_node *current_node = *head;
//	s_st_node* last_node = head;
//	s_st_node* last_edge = NULL;
//	int rule_cursor = 0;
//
//	s_st_node *merge_node_start = NULL;
//
//	while (1) {
//		if (escape_flag) {
//			ACC_FUNC acc_func;
//			switch(rule[rule_cursor]){
//			case ST_RULE_ESCAPE_LOWER_CASE_CHAR:
//				acc_func = lower_case_char_acc_func;
//				break;
//			case ST_RULE_ESCAPE_HIGHER_CASE_CHAR:
//				acc_func = higher_case_char_acc_func;
//				break;
//			case ST_RULE_ESCAPE_NUMBER_CHAR:
//				acc_func = number_char_acc_func;
//				break;
//			case ST_RULE_ESCAPE_IDENTIFIER_CHAR:
//				acc_func = identifier_char_acc_func;
//				break;
//			case ST_RULE_ESCAPE_BLANK_CHAR:
//				acc_func = blank_char_acc_func;
//				break;
//			default:
//				return INVALID_ARGUMENT;
//			}
//
//			s_st_edge* current_edge = current_node->edges;
//			while(current_edge != NULL){
//				if(current_edge->acc_func == acc_func){
//					break;
//				}
//
//				current_edge = current_edge->next;
//			}
//
//			if(current_edge == NULL){
//				st_new_edge(&current_edge);
//				current_edge->acc_func = acc_func;
//				current_edge->next = current_node->edges;
//
//				s_st_node* new_node;
//				st_new_node(&new_node);
//
//				current_edge->target_node = new_node;
//			}
//
//			escape_flag = FALSE;
//			last_node = current_node;
//			current_node = current_edge->target_node;
//			last_edge = current_edge;
//			++rule_cursor;
//		} else {
//			switch(rule[rule_cursor]){
//			case ST_RULE_ESCAPE:
//				escape_flag = TRUE;
//				break;
//			case ST_RULE_MERGE_START:
//
//			case ST_RULE_MERGE_END:
//
//			case ST_RULE_ANY_CHAR:
//			{
//				s_st_edge* current_edge = current_node->edges;
//				while(current_edge != NULL){
//					if(ACCEPT_ANY_CHAR(current_edge)){
//						break;
//					}
//					current_edge = current_edge->next;
//				}
//
//			}
//			break;
//			case ST_RULE_ZERO_OR_MORE:
//			case ST_RULE_ONE_OR_MORE:
//			default:
//
//			}
//		}
//
//	}
//
//	return SUCCESS;
//}

int st_build_new_st(sSTNode **head) {
	*head = (sSTNode*) malloc(sizeof(sSTNode));

	(*head)->first_edge = NULL;
	(*head)->node_attr = NODE_ATTR_START;

	return SUCCESS;
}

int st_new_node(sSTNode **node) {
	*node = (sSTNode*) malloc(sizeof(sSTNode));

	(*node)->first_edge = NULL;
	(*node)->node_attr = NODE_ATTR_NORMAL;

	return SUCCESS;
}

int st_new_edge(sSTEdge **edge) {
	*edge = (sSTEdge*) malloc(sizeof(sSTEdge));

	(*edge)->acc_func = NULL;
	(*edge)->data = NULL;
	(*edge)->next = NULL;
	(*edge)->target_node = NULL;

	return SUCCESS;
}

int st_merge(sSTNode** head, sSTNode* path){
	if(path == NULL || head == NULL || path->first_edge == NULL){
		return INVALID_ARGUMENT;
	}

	if(*head == NULL){
		*head = path;
		return SUCCESS;
	}

	sSTEdge* edge = path->first_edge;
	while(edge->next != NULL){
		edge = edge->next;
	}

	edge->next = (*head)->first_edge;
	(*head)->first_edge = edge;

	st_free_node(path);

	return SUCCESS;
}

int st_free_node(sSTNode* node){
	free(node);

	return SUCCESS;
}

int st_free_edge(sSTEdge* edge){
	free(edge);

	return SUCCESS;
}

