/*
 * buffer.c
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#include <modules/mm/buffer.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_DEFAULT_SIZE (4096)

struct sBuffer {
	void *data;
	size_t size;
	size_t cursor;
};

sBuffer* buffer_new(size_t size) {
	sBuffer *buffer;
	if (size == 0) {
		buffer = (sBuffer*) malloc(sizeof(sBuffer) + BUFFER_DEFAULT_SIZE);
		buffer->size = BUFFER_DEFAULT_SIZE;
	} else {
		buffer = (sBuffer*) malloc(sizeof(sBuffer) + size);
		buffer->size = size;
	}

	buffer->cursor = 0;
	buffer->data = (char*) buffer + sizeof(sBuffer);

	return buffer;
}

void* buffer_write(sBuffer *buffer, void *data, size_t size) {
	if (size + buffer->cursor > buffer->size) {
		return NULL;
	}

	memcpy(&((char*) buffer->data)[buffer->cursor], data, size);
	buffer->cursor += size;
	((char*)buffer->data)[buffer->cursor] = '\0';

	return &((char*)buffer->data)[buffer->cursor - size];
}

void* buffer_write_byte(sBuffer *buffer, char data) {
	if (buffer->cursor == buffer->size) {
		return NULL;
	}

	((char*) buffer->data)[buffer->cursor] = data;
	++buffer->cursor;
	((char*)buffer->data)[buffer->cursor] = '\0';

	return &((char*)buffer->data)[buffer->cursor - 1];
}

void* buffer_read(sBuffer *buffer, size_t start) {
	if (start >= buffer->size) {
		return NULL;
	}

	return (char*) buffer->data + start;
}

void buffer_clear(sBuffer *buffer) {
	buffer->cursor = 0;
}

size_t buffer_capacity(sBuffer *buffer) {
	return buffer->size;
}

size_t buffer_used_space(sBuffer *buffer) {
	return buffer->cursor;
}

void buffer_destroy(sBuffer *buffer) {
	free(buffer);
}
