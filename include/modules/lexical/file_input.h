/*
 * file_input.h
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_FILE_INPUT_H_
#define INCLUDE_MODULES_LEXICAL_FILE_INPUT_H_

#include <errcode.h>
#include <stdio.h>
#include <modules/mm/mm.h>

#define INPUT_BUFFER_SIZE (4096)

typedef struct sInputSourceDesc{
	FILE* input_file_ptr;
	size_t input_file_cursor;
	int input_source_attr;
} sInputSourceDesc;

typedef struct sInputBufferDesc{
	char* buffer_arr_ptr[2];
	int buffer_attr;
} sInputBufferDesc;

sInputSourceDesc* open_input_source(char*);
int fill_buffer(sInputSourceDesc*, sInputBufferDesc*);
int close_input_source(sInputSourceDesc*);


#endif /* INCLUDE_MODULES_LEXICAL_FILE_INPUT_H_ */
