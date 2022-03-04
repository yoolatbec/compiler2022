/*
 * file_input.c
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */

#include <stdio.h>

#include <modules/lexical/file_input.h>

#define FALSE (0)
#define TRUE (!FALSE)

#define INPUT_CURSOR_DEFAULT (0)

int fill_buffer(input_source_desc *input_src, buffer_desc *buffer) {
	if (input_src == NULL || buffer == NULL || input_src->input_file_ptr == NULL) {
		return INVALID_ARGUMENT;
	}

	if (input_src->input_source_attr & INPUT_SOURCE_CLOSED) {
		return FILE_INPUT_SOURCE_CLOSED;
	}

	if (input_src->input_source_attr & INPUT_SOURCE_FINISHED) {
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

int close_input_source(input_source_desc *input_src) {
	if (input_src == NULL || input_src->input_file_ptr == NULL) {
		return INVALID_ARGUMENT;
	}

	fclose(input_src->input_file_ptr);

	input_src->input_source_attr = input_src->input_source_attr
			| INPUT_SOURCE_CLOSED;

	return SUCCESS;
}

