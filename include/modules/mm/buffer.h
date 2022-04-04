/*
 * buffer.h
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_MM_BUFFER_H_
#define INCLUDE_MODULES_MM_BUFFER_H_

#include <stddef.h>

typedef struct sBuffer sBuffer;

sBuffer* buffer_new(size_t);
void* buffer_write(sBuffer*, void*, size_t);
void* buffer_write_byte(sBuffer*, char);
void* buffer_read(sBuffer*, size_t);
void buffer_clear(sBuffer*);
size_t buffer_capacity(sBuffer*);
size_t buffer_used_space(sBuffer*);

void buffer_destroy(sBuffer*);

#endif /* INCLUDE_MODULES_MM_BUFFER_H_ */
