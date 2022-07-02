/*
 * by_effect_func.h
 *
 *  Created on: 6 Mar 2022
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_BY_EFFECT_FUNC_H_
#define INCLUDE_MODULES_LEXICAL_BY_EFFECT_FUNC_H_

#include <utils/linked_list.h>
#include <modules/mm/buffer.h>

typedef struct sPrimitive sPrimitive;

/*
 * 附加在有限状态机的边上。
 * 当通过该边进行跳转时执行对应的动作。
 */
typedef void (*EDGE_BY_FUNC)(char, void*);

/*
 * 附加在有限状态机的终止节点上。
 * 当完成对一个语法符号的识别后执行对应的动作。
 */
typedef void (*PRIMITIVE_BY_FUNC)(sPrimitive*, sLinkedListNode**, sBuffer*);

/*
 * 将识别的字符添加到缓冲中
 */
void append_to_buffer_by_func(char, void*);

/*
 * 完成对一个标识符的识别
 * 将一个代表该标识符的语法符号添加到符号序列中，并初始化这个语法符号的属性，
 * 如字面值，哈希值
 */
void identifier_primitive_by_func(sPrimitive*, sLinkedListNode**, sBuffer*);

/*
 * 完成对一个十进制数字的识别
 * 将一个代表十进制数字的语法符号添加到符号序列中，并初始化这个语法符号的属性
 * 如字面值，哈希值
 */
void integer_primitive_by_func(sPrimitive*, sLinkedListNode**, sBuffer*);

/*
 * 完成对一个八进制数字的识别
 * 将一个代表八进制数字的语法符号添加到符号序列中，并初始化这个语法符号的属性
 * 如字面值，哈希值
 */
void octal_integer_primitive_by_func(sPrimitive*, sLinkedListNode**, sBuffer*);

#endif /* INCLUDE_MODULES_LEXICAL_BY_EFFECT_FUNC_H_ */
