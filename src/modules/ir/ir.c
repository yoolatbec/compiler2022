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
	while (IRs != NULL) {
		IR *ir = linked_list_first(IRs);
		IRs = linked_list_remove_first(IRs);

		printf("result: %d, op: %d, oprand0: %d, oprand1: %d\n", ir->result,
				ir->op, ir->oprand0, ir->oprand1);

		free(ir);
	}
}
