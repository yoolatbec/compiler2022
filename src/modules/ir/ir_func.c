/*
 * ir_func.c
 *
 *  Created on: 2022年5月14日
 *      Author: yoolatbec
 */

#include <modules/ir/ir_func.h>
#include <reserved_word.h>
#include <stdlib.h>
#include <stdio.h>

void push_oprands(void *data) {
	sContext *context = (sContext*) data;
	context->oprands = linked_list_append(context->oprands,
			(void*) context->parameter);
	puts("push oprand");
}

void push_ops(void *data) {
	sContext *context = (sContext*) data;
	context->ops = linked_list_append(context->ops, (void*) context->parameter);
	puts("push op");
}

void create_IR(void *data) {
	puts("create IR");
	sContext *context = (sContext*) data;
	IR *ir = (IR*) malloc(sizeof(IR));

	ir->op = (int) linked_list_last(context->ops);
	context->ops = linked_list_remove_last(context->ops);

	ir->oprand1 = (int) linked_list_last(context->oprands);
	context->oprands = linked_list_remove_last(context->oprands);

	ir->oprand0 = (int) linked_list_last(context->oprands);
	context->oprands = linked_list_remove_last(context->oprands);

	ir->result = context->next_assign_label;
	++context->next_assign_label;

	context->oprands = linked_list_append(context->oprands, (void*) ir->result);
	context->IRs = linked_list_append(context->IRs, ir);
}

void push_imme(void *data) {
	puts("push imme");
	sContext *context = (sContext*) data;

	sPrimitive *primitive = context->primitive;
	context->oprands = linked_list_append(context->oprands,
			(void*) primitive_get_value(primitive));
	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = LOAD_IMME;
	ir->oprand0 = primitive_get_value(primitive);
	ir->oprand1 = 0;
	ir->result = context->next_assign_label;
	context->next_assign_label++;
	context->IRs = linked_list_append(context->IRs, ir);
}

void new_var(void *data) {
	puts("new variable");
	sContext *context = (sContext*) data;

	sPrimitive *primitive = context->primitive;
	sVariable *v = (sVariable*) malloc(sizeof(sVariable));
	v->hashcode = primitive_get_hashcode(primitive);
	v->literal_value = primitive_get_literal_value(primitive);
	v->offset = context->stack_offset;
	context->stack_offset += 4;
	context->variable = linked_list_append(context->variable, v);

	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = NEW_VAR;
	ir->result = context->next_assign_label;
	ir->oprand0 = 0;
	ir->oprand1 = 0;
	context->next_assign_label++;
	context->IRs = linked_list_append(context->IRs, ir);
}

void load_var(void *data) {
	puts("load variable");
	sContext *context = (sContext*) data;

	sPrimitive *primitive = context->primitive;
	int size = linked_list_size(context->variable);
	sVariable *v = NULL;
	for (int i = 0; i < size; i++) {
		v = (sVariable*) linked_list_nth(context->variable, i);
		if (v->hashcode == primitive_get_hashcode(primitive)) {
			break;
		}
	}

	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = LOAD;
	ir->result = context->next_assign_label;
	context->next_assign_label++;
	ir->oprand0 = v->offset;
	ir->oprand1 = 0;
	context->oprands = linked_list_append(context->oprands, (void*) ir->result);
	context->IRs = linked_list_append(context->IRs, ir);
}

void store_var(void *data) {
	puts("store variable");
	sContext *context = (sContext*) data;

	sPrimitive *primitive = context->primitive;
	int size = linked_list_size(context->variable);
	sVariable *v = NULL;
	for (int i = 0; i < size; i++) {
		v = (sVariable*) linked_list_nth(context->variable, i);
		if (v->hashcode == primitive_get_hashcode(primitive)) {
			break;
		}
	}

	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = STORE;
	ir->oprand1 = (int) linked_list_last(context->oprands);
	context->oprands = linked_list_remove_last(context->oprands);
	ir->oprand0 = (int) linked_list_last(context->oprands);
	context->oprands = linked_list_remove_last(context->oprands);
	ir->result = 0;
	context->IRs = linked_list_append(context->IRs, ir);
}

void load_var_addr(void *data) {
	puts("load variable address");
	sContext *context = (sContext*) data;

	sPrimitive *primitive = context->primitive;
	int size = linked_list_size(context->variable);
	sVariable *v = NULL;
	for (int i = 0; i < size; i++) {
		v = (sVariable*) linked_list_nth(context->variable, i);
		if (v->hashcode == primitive_get_hashcode(primitive)) {
			break;
		}
	}

	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = LOAD_ADDR;
	ir->oprand0 = v->offset;
	ir->result = context->next_assign_label;
	context->next_assign_label++;
	context->oprands = linked_list_append(context->oprands, (void*) v->offset);
	context->IRs = linked_list_append(context->IRs, ir);
}

void switch_list(void *data) {
	puts("switch list");
	sContext *context = (sContext*) data;

	context->conditional_IRs = context->IRs;
	context->IRs = NULL;
}

void switch_back_list(void *data) {
	puts("switch back list");
	sContext *context = (sContext*) data;

	sLinkedListNode *temp = context->IRs;
	context->IRs = context->conditional_IRs;
	context->conditional_IRs = temp;
}

void append_conditional_list(void *data) {
	puts("append conditional list");
	sContext *context = (sContext*) data;

	while (context->conditional_IRs != NULL) {
		IR *ir = (IR*) linked_list_first(context->conditional_IRs);
		context->conditional_IRs = linked_list_remove_first(
				context->conditional_IRs);
		context->IRs = linked_list_append(context->IRs, ir);
	}
}

void create_label(void *data) {
	puts("create label");

	sContext *context = (sContext*) data;

	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = LABEL;
	ir->result = (int) linked_list_first(context->label_stack);
	context->label_stack = linked_list_remove_first(context->label_stack);
	ir->oprand0 = 0;
	ir->oprand1 = 0;
	context->IRs = linked_list_append(context->IRs, ir);
}

void create_goto(void *data) {
	puts("create goto");

	sContext *context = (sContext*) data;
	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = GOTO;
	ir->result = 0;
	ir->oprand0 = (int) linked_list_first(context->goto_stack);
	context->goto_stack = linked_list_remove_first(context->goto_stack);
	ir->oprand1 = 0;
	context->IRs = linked_list_append(context->IRs, ir);
}

void clear_label_stack(void *data) {
	puts("clear label stack");

	sContext *context = (sContext*) data;
	while (context->label_stack != NULL) {
		context->label_stack = linked_list_remove_first(context->label_stack);
	}

	while (context->goto_stack != NULL) {
		context->goto_stack = linked_list_remove_first(context->goto_stack);
	}
}

void load_label_stack_if(void *data) {
	puts("load label stack if");

	sContext *context = (sContext*) data;
	int label = context->next_assign_label;
	context->next_assign_label += 3;

	context->goto_stack = linked_list_append(context->goto_stack,
			(void*) (label + 1));
	context->goto_stack = linked_list_append(context->goto_stack,
			(void*) (label + 2));
	context->goto_stack = linked_list_append(context->goto_stack,
			(void*) label);

	context->label_stack = linked_list_append(context->label_stack,
			(void*) label);
	context->label_stack = linked_list_append(context->label_stack,
			(void*) (label + 1));
	context->label_stack = linked_list_append(context->label_stack,
			(void*) (label + 2));
}

void create_if(void *data) {
	puts("create if");
	sContext *context = (sContext*) data;

	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = RW_ID_IF;
	ir->oprand0 = (int) linked_list_first(context->goto_stack);
	context->goto_stack = linked_list_remove_first(context->goto_stack);
	ir->result = 0;
	ir->oprand1 = 0;
	context->IRs = linked_list_append(context->IRs, ir);
}

void create_while(void *data) {
	puts("create while");

	sContext *context = (sContext*) data;
	IR *ir = (IR*) malloc(sizeof(IR));
	ir->op = RW_ID_WHILE;
	ir->oprand0 = (int) linked_list_first(context->goto_stack);
	context->goto_stack = linked_list_remove_first(context->goto_stack);
	ir->result = 0;
	ir->oprand1 = 0;
	context->IRs = linked_list_append(context->IRs, ir);
}

void load_label_stack_while(void *data) {
	puts("load label stack while");

	sContext *context = (sContext*) data;

	int label = context->next_assign_label;
	context->next_assign_label += 2;

	context->label_stack = linked_list_append(context->label_stack,
			(void*) label);
	context->label_stack = linked_list_append(context->label_stack,
			(void*) (label + 1));

	context->goto_stack = linked_list_append(context->goto_stack,
			(void*) (label + 1));
	context->goto_stack = linked_list_append(context->goto_stack,
			(void*) label);
}
