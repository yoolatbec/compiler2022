/*
 * file_input.c
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */

#include <stdio.h>
#include <stdlib.h>

#include <modules/lexical/file_input.h>

#define FALSE (0)
#define TRUE (!FALSE)

#define INPUT_CURSOR_DEFAULT (0)

#define INPUT_SOURCE_FINISHED (1 << 0)
#define INPUT_SOURCE_CLOSED (1 << 1)
#define BUFFER_0_UNFILLED (1 << 0)
#define BUFFER_1_UNFILLED (1 << 1)

#define INPUT_SOURCE_IS_CLOSED(src) (src->input_source_attr & INPUT_SOURCE_CLOSED)
#define INPUT_SOURCE_IS_FINISHED(src) (src->input_source_attr & INPUT_SOURCE_FINISHED)

int fill_buffer(sInputSourceDesc *input_src, sInputBufferDesc *buffer) {
	if (input_src == NULL || buffer == NULL || input_src->input_file_ptr == NULL) {
		return INVALID_ARGUMENT;
	}

	if (INPUT_SOURCE_IS_CLOSED(input_src)) {
		return FILE_INPUT_SOURCE_CLOSED;
	}

	if (INPUT_SOURCE_IS_FINISHED(input_src)) {
		return FILE_UNREAD_CONTENT_NULL;
	}

	char *target_buffer;
	if (buffer->buffer_attr & BUFFER_0_UNFILLED) {
		target_buffer = buffer->buffer_arr_ptr[0];
	} else if (buffer->buffer_attr & BUFFER_1_UNFILLED) {
		target_buffer = buffer->buffer_arr_ptr[1];
	} else {
		return BUFFER_NOT_AVAILABLE;
	}

	size_t rd_count = fread(target_buffer, 1, INPUT_BUFFER_SIZE,
			input_src->input_file_ptr);

	if (rd_count == 0) {
		input_src->input_source_attr = input_src->input_source_attr
				| INPUT_SOURCE_FINISHED;
		return FILE_UNREAD_CONTENT_NULL;
	}

	if (rd_count < 4096) {
		input_src->input_source_attr = input_src->input_source_attr
				| INPUT_SOURCE_FINISHED;
	}

	if (buffer->buffer_attr & BUFFER_0_UNFILLED) {
		buffer->buffer_attr = buffer->buffer_attr & (~BUFFER_0_UNFILLED);
	} else if (buffer->buffer_attr & BUFFER_1_UNFILLED) {
		buffer->buffer_attr = buffer->buffer_attr & (~BUFFER_1_UNFILLED);
	}

	return SUCCESS;
}

int close_input_source(sInputSourceDesc *input_src) {
	if (input_src == NULL || input_src->input_file_ptr == NULL) {
		return INVALID_ARGUMENT;
	}

	fclose(input_src->input_file_ptr);

	input_src->input_source_attr = input_src->input_source_attr
			| INPUT_SOURCE_CLOSED;

	return SUCCESS;
}

sInputSourceDesc* open_input_source(char *path) {
	FILE *file = fopen(path, "r");

	if (file == NULL) {
		return NULL;
	}

	sInputSourceDesc *desc = (sInputSourceDesc*) malloc(
			sizeof(sInputSourceDesc));
	desc->input_file_ptr = file;
	desc->input_file_cursor = INPUT_CURSOR_DEFAULT;
	desc->input_source_attr = 0;

	return desc;
}
