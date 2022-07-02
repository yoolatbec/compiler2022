/*
 * ir.c
 *
 *  Created on: 2022年5月14日
 *      Author: yoolatbec
 */

#include <modules/ir/ir.h>
#include <stdio.h>
#include <stdlib.h>

void print_IRs(sLinkedListNode *IRs, int base_label) {
	size_t len = linked_list_size(IRs);

	for (int i = 0; i < len; i++) {
		IR *ir = linked_list_nth(IRs, i);
		printf("opcode: %d, oprand0: %d, oprand1: %d, result id: %d\n",
				ir->op, ir->oprand0, ir->oprand1, ir->result);
	}
}
