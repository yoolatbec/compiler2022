/*
 * ir_func.h
 *
 *  Created on: 2022年5月14日
 *      Author: yoolatbec
 */

#ifndef SRC_MODULES_IR_IR_FUNC_H_
#define SRC_MODULES_IR_IR_FUNC_H_

#include <utils/linked_list.h>
#include <modules/lexical/primitive.h>
#include <modules/ir/ir.h>

/*
 * 生成中间表示所需要的上下文信息
 */
typedef struct sContext {
	sLinkedListNode *oprands;  //操作数栈
	sLinkedListNode *ops;  //操作类型栈
	sLinkedListNode *IRs;  //生成的中间表示序列
	sLinkedListNode *label_stack;  //符号栈，用于条件跳转和循环
	sLinkedListNode *goto_stack;  //跳转符号栈
	sLinkedListNode *variable;  //符号表
	sLinkedListNode *conditional_IRs;  //临时中间表示序列，用于条件判断语句和循环语句
	int label_base;  //首标签
	int next_assign_label;  //下一个分配的标签
	int stack_offset;  //栈偏移，表示已使用的栈空间
	int parameter;  //参数
	sPrimitive *primitive;  //参数
} sContext;

/*
 * 语法分析动作
 */

void push_oprands(void*);  //将一个操作数压栈
void push_ops(void*);  //将一个操作类型压栈
void push_imme(void*);  //将一个立即数入栈
void new_var(void*);  //分配一个新的变量，生成一条中间表示
void create_IR(void*);  //创建一条表示运算的中间表示
void create_if(void*);  //创建一条表示条件判断跳转的中间表示
void create_while(void*);  //创建一条表示循环跳转的中间表示
void load_var(void*);  //创建一条表示加载变量值的中间表示
void store_var(void*);  //创建一条表示保存变量之的中间表示
void load_var_addr(void*);  //创建一条表示加载变量地址的中间表示
void switch_list(void*);  //更改保存生成的中间表示的序列
void switch_back_list(void*);  //同上
void append_conditional_list(void*);  //将临时中间表示列表中的中间表示添加到主序列中
void create_label(void*);  //创建一条表示生成标签的中间表示
void create_goto(void*);  //创建一条表示无条件跳转的中间表示
void clear_label_stack(void*);  //清空标签栈中的所有标签
void load_label_stack_if(void*);  //将用于条件跳转语句的标签加入到标签栈
void load_label_stack_while(void*);  //将用于循环语句的标签加入到标签栈

#endif /* SRC_MODULES_IR_IR_FUNC_H_ */
