/*
 * file_input.h
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_FILE_INPUT_H_
#define INCLUDE_MODULES_LEXICAL_FILE_INPUT_H_

#include <errcode.h>
#include <modules/mm/mm.h>

#define INPUT_SOURCE_FINISHED (1 << 0)
#define INPUT_SOURCE_CLOSED (1 << 1)

#define INPUT_BUFFER_SIZE (4096)
#define BUFFER_0_UNFILLED (1 << 0)
#define BUFFER_1_UNFILLED (1 << 1)

typedef struct input_source_desc{
	FILE* input_file_ptr;
	size_t input_file_cursor;
	int input_source_attr;
} input_source_desc;

typedef struct buffer_desc{
	char* buffer_arr_ptr[2];
	int buffer_attr;
} buffer_desc;

int fill_buffer(input_source_desc*, buffer_desc*);
int close_input_source(input_source_desc*);


#endif /* INCLUDE_MODULES_LEXICAL_FILE_INPUT_H_ */
