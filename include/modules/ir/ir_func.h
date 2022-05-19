/*
 * ir_func.h
 *
 *  Created on: 2022年5月14日
 *      Author: yoolatbec
 */

#ifndef SRC_MODULES_IR_IR_FUNC_H_
#define SRC_MODULES_IR_IR_FUNC_H_

#include <utils/linked_list.h>
#include <modules/ir/ir.h>

typedef struct sContext {
	sLinkedListNode* oprands;
	sLinkedListNode* ops;
	sLinkedListNode* IRs;
	int label_base;
	int next_assign_label;
	int parameter;
} sContext;

void push_oprands(void*);
void push_ops(void*);
void create_IR(void*);

#endif /* SRC_MODULES_IR_IR_FUNC_H_ */
