/*
 * primitive.h
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_PRIMITIVE_H_
#define INCLUDE_MODULES_LEXICAL_PRIMITIVE_H_

typedef struct sPrimitive sPrimitive;

sPrimitive* primitive_new_with_type(int);
void primitive_set_literal_value(sPrimitive*, char*);
void primitive_destroy(sPrimitive*);
int primitive_get_type(sPrimitive*);

#endif /* INCLUDE_MODULES_LEXICAL_PRIMITIVE_H_ */
