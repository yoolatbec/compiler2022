/*
 * primitive.h
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_PRIMITIVE_H_
#define INCLUDE_MODULES_LEXICAL_PRIMITIVE_H_

/*
 * 用于表示一个语法符号的结构
 */
typedef struct sPrimitive sPrimitive;

sPrimitive* primitive_new_with_type(int);
void primitive_set_literal_value(sPrimitive*, char*);
char* primitive_get_literal_value(sPrimitive*);
void primitive_destroy(sPrimitive*);
int primitive_get_type(sPrimitive*);
void primitive_set_value(sPrimitive*, long);
long primitive_get_value(sPrimitive*);
void primitive_set_hashcode(sPrimitive*, long);
long primitive_get_hashcode(sPrimitive*);

#endif /* INCLUDE_MODULES_LEXICAL_PRIMITIVE_H_ */
