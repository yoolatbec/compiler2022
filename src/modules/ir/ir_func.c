/*
 * ir_func.c
 *
 *  Created on: 2022年5月14日
 *      Author: yoolatbec
 */

#include <modules/ir/ir_func.h>
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
