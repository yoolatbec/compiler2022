/*
 * ir.h
 *
 *  Created on: 2022年5月14日
 *      Author: yoolatbec
 */

#ifndef SRC_MODULES_IR_IR_H_
#define SRC_MODULES_IR_IR_H_
#include <utils/linked_list.h>

typedef struct sIR {
	int result;
	int op;
	int oprand0;
	int oprand1;
} IR;

void print_IRs(sLinkedListNode*, int);

#endif /* SRC_MODULES_IR_IR_H_ */
