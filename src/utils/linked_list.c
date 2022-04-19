/*
 * linked_list.c
 *
 *  Created on: 5 Mar 2022
 *      Author: yoolatbec
 */

#include <utils/linked_list.h>
#include <stdlib.h>

#define FALSE (0)
#define TRUE (!FALSE)

struct sLinkedListNode {
	sLinkedListNode *next;
	sLinkedListNode *prev;
	void *data;
};

sLinkedListNode* linked_list_append(sLinkedListNode *head, void *data) {
	if (head == NULL) {
		head = (sLinkedListNode*) malloc(sizeof(sLinkedListNode));
		head->data = data;
		head->next = NULL;
		head->prev = NULL;

		return head;
	}

	sLinkedListNode *new_node = (sLinkedListNode*) malloc(
			sizeof(sLinkedListNode));
	new_node->data = data;
	new_node->next = head;
	new_node->prev = head->prev;
	head->prev = new_node;

	if (head->next == NULL) {
		head->next = new_node;
		new_node->prev = head;
	} else {
		new_node->prev->next = new_node;
	}

	return head;
}

sLinkedListNode* linked_list_prepend(sLinkedListNode *head, void *data) {
	if (head == NULL) {
		head = (sLinkedListNode*) malloc(sizeof(sLinkedListNode));
		head->data = data;
		head->next = NULL;
		head->prev = NULL;

		return head;
	}

	sLinkedListNode *new_node = (sLinkedListNode*) malloc(
			sizeof(sLinkedListNode));
	new_node->data = data;
	new_node->next = head;
	new_node->prev = head->prev;
	head->prev = new_node;

	if (head->next == NULL) {
		head->next = new_node;
		new_node->prev = head;
	} else {
		new_node->prev->next = new_node;
	}

	return new_node;
}

sLinkedListNode* linked_list_insert(sLinkedListNode *head, void *data,
		size_t position) {
	if (head == NULL) {
		return linked_list_append(head, data);
	}

	if (position == 0) {
		return linked_list_prepend(head, data);
	}

	if (head->next == NULL) {
		return linked_list_append(head, data);
	}

	sLinkedListNode *current = head;
	while (position != 0) {
		current = current->next;
		--position;
	}

	linked_list_prepend(current, data);

	return head;
}

sLinkedListNode* linked_list_remove_first(sLinkedListNode *head) {
	if (head == NULL) {
		return NULL;
	}

	if (head->next == NULL) {
		free(head);
		return NULL;
	}

	sLinkedListNode *new_head = head->next;
	if (head->next != head->prev) {
		head->next->prev = head->prev;
		head->prev->next = head->next;
	} else {
		head->next->prev = NULL;
		head->prev->next = NULL;
	}

	free(head);

	return new_head;
}

sLinkedListNode* linked_list_remove_last(sLinkedListNode *head) {
	if (head == NULL) {
		return NULL;
	}

	if (head->prev == NULL) {
		free(head);
		return NULL;
	}

	sLinkedListNode *last = head->prev;
	if (last == head->next) {
		head->next = NULL;
		head->prev = NULL;
	} else {
		head->prev = last->prev;
		last->prev->next = head;
	}

	free(last);

	return head;
}

sLinkedListNode* linked_list_remove(sLinkedListNode *head, void *data) {
	if (head == NULL) {
		return NULL;
	}

	if (head->data == data) {
		return linked_list_remove_first(head);
	}

	sLinkedListNode *current = head->next;
	while (current != NULL && current != head) {
		if (current->data == data) {
			linked_list_remove_first(current);
			break;
		}

		current = current->next;
	}

	return head;
}

sLinkedListNode* linked_list_remove_nth(sLinkedListNode *head, size_t position) {
	if (head == NULL) {
		return NULL;
	}

	if (position == 0) {
		return linked_list_remove_first(head);
	}

	if (head->next == NULL) {
		return head;
	}

	sLinkedListNode *current = head;
	while (position > 0) {
		current = current->next;
		--position;
	}

	if (current == head) {
		head = head->next;
	}
	linked_list_remove_first(current);

	return head;
}

void* linked_list_first(sLinkedListNode *head) {
	if (head == NULL) {
		return NULL;
	}

	return head->data;
}

void* linked_list_last(sLinkedListNode *head) {
	if (head == NULL) {
		return NULL;
	}

	if (head->prev == NULL) {
		return head->data;
	}

	return head->prev->data;
}

void* linked_list_nth(sLinkedListNode *head, size_t position) {
	if (head == NULL) {
		return NULL;
	}

	if (position == 0 || head->next == NULL) {
		return head->data;
	}

	sLinkedListNode *current = head;
	while (position > 0) {
		current = current->next;
		--position;
	}

	return current->data;
}

size_t linked_list_size(sLinkedListNode *head) {
	if (head == NULL) {
		return 0;
	}

	if (head->next == NULL) {
		return 1;
	}

	size_t size = 1;
	sLinkedListNode *current = head;
	while (current->next != head) {
		++size;
		current = current->next;
	}

	return size;
}

sLinkedListNode* linked_list_clear(sLinkedListNode *head) {
	while (head != NULL) {
		head = linked_list_remove_first(head);
	}

	return NULL;
}

int linked_list_contains(sLinkedListNode *head, void *data) {
	if (head == NULL) {
		return FALSE;
	}

	if (head->next == NULL) {
		return head->data == data;
	}

	sLinkedListNode *current = head;
	do {
		if (current->data == data) {
			return TRUE;
		}

		current = current->next;
	} while (current != head);

	return FALSE;
}
