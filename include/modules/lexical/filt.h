/*
 * filt.h
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_FILT_H_
#define INCLUDE_MODULES_LEXICAL_FILT_H_

#include <errcode.h>
#include <modules/mm/mm.h>
#include <modules/lexical/file_input.h>
#include <utils/linked_list.h>

typedef struct primitive {
	char *value;
	int primitive_attr;
} primitive;

typedef struct primitive_value_buffer {
	char *value_arr_ptr;
	size_t cursor;
	struct primitive_value_buffer *next;
} primitive_value_buffer;



#endif /* INCLUDE_MODULES_LEXICAL_FILT_H_ */
