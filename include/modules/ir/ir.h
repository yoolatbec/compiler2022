/*
 * ir.h
 *
 *  Created on: 2022年5月14日
 *      Author: yoolatbec
 */

#ifndef SRC_MODULES_IR_IR_H_
#define SRC_MODULES_IR_IR_H_
#include <utils/linked_list.h>

/*
 * 中间表示
 */
typedef struct sIR {
	int result;  //结果标签
	int op;  //操作类型
	int oprand0;  //第一个操作数
	int oprand1;  //第二个操作数
} IR;

/*
 * 变量信息
 */
typedef struct sVariable {
	long hashcode;  //哈希
	char* literal_value;  //字面值
	long offset;  //栈地址偏移
} sVariable;

//部分操作类型
#define LOAD (1024)
#define STORE (1025)
#define NEW_VAR (1026)
#define LOAD_ADDR (1027)
#define LOAD_IMME (1028)
#define LABEL (1029)
#define GOTO (1030)

/*
 * 用于打印序列中的中间表示
 */
void print_IRs(sLinkedListNode*, int);

#endif /* SRC_MODULES_IR_IR_H_ */
