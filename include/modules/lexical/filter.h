/*
 * filter.h
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_FILTER_H_
#define INCLUDE_MODULES_LEXICAL_FILTER_H_

#include <errcode.h>
#include <modules/mm/mm.h>
#include <modules/lexical/file_input.h>

typedef struct primitive {
	char* value;
	int primitive_attr;
	struct primitive* next;
} primitive;

typedef struct primitive_value_buffer{
	char* value_arr_ptr;
	size_t cursor;
	struct primitive_value_buffer* next;
} primitive_value_buffer;

int filt(buffer_desc*, sSTNode*, primitive*, primitive_value_buffer*);

#endif /* INCLUDE_MODULES_LEXICAL_FILTER_H_ */
