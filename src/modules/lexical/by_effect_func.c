/*
 * by_effect_func.c
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#include <modules/lexical/by_effect_func.h>
#include <modules/mm/buffer.h>

#include <stdio.h>

/*
 * 将当前字符添加到缓冲
 */
void append_to_buffer_by_func(char c, void *data) {
	sBuffer *buffer = (sBuffer*) data;

	buffer_write_byte(buffer, c);
}

/*
 * 完成对标识符的识别
 */
void identifier_primitive_by_func(sPrimitive *primitive,
		sLinkedListNode **values, sBuffer *buffer) {
	size_t len = buffer_used_space(buffer) + 1;
	sBuffer *valueBuffer = NULL;

	//查找缓冲区列表，试图获得一个可以容纳标识符字面值的缓冲
	int count = linked_list_size(*values);
	for (int i = 0; i < count; i++) {
		sBuffer *b = linked_list_nth(*values, i);
		if (buffer_available(b) >= len) {
			valueBuffer = b;
			break;
		}
	}

	if (valueBuffer == NULL) {
		valueBuffer = buffer_new(
		BUFFER_DEFAULT_SIZE > len ? BUFFER_DEFAULT_SIZE : len);
		*values = linked_list_append(*values, valueBuffer);
	}

	//将标识符的字面值写入到缓冲区
	char *value = buffer_write(valueBuffer, buffer_head(buffer), len);
	buffer_write_byte(valueBuffer, '\0');

	//计算哈希值
	long hashcode = 0;

	for (size_t i = 0; i < len; i++) {
		hashcode = hashcode * 233 + value[i];
	}

	//更新属性
	primitive_set_literal_value(primitive, value);
	primitive_set_value(primitive, (long) value);
	primitive_set_hashcode(primitive, hashcode);

	buffer_clear(buffer);
}

void integer_primitive_by_func(sPrimitive *primitive, sLinkedListNode **values,
		sBuffer *buffer) {
	size_t len = buffer_used_space(buffer) + 1;
	sBuffer *valueBuffer = NULL;

	//查找缓冲区列表，试图获得一个可以容纳标识符字面值的缓冲
	int count = linked_list_size(*values);
	for (int i = 0; i < count; i++) {
		sBuffer *b = linked_list_nth(*values, i);
		if (buffer_available(b) >= len) {
			valueBuffer = b;
			break;
		}
	}

	if (valueBuffer == NULL) {
		valueBuffer = buffer_new(
		BUFFER_DEFAULT_SIZE > len ? BUFFER_DEFAULT_SIZE : len);
		*values = linked_list_append(*values, valueBuffer);
	}

	//将标识符的字面值写入到缓冲区
	char *value = buffer_write(valueBuffer, buffer_head(buffer), len);
	buffer_write_byte(valueBuffer, '\0');

	//计算哈希值
	long hashcode = atol(value);

	//更新属性
	primitive_set_literal_value(primitive, value);
	primitive_set_value(primitive, hashcode);
	primitive_set_hashcode(primitive, hashcode);

	buffer_clear(buffer);
}

void octal_integer_primitive_by_func(sPrimitive *primitive,
		sLinkedListNode **values, sBuffer *buffer) {
	size_t len = buffer_used_space(buffer) + 1;
	sBuffer *valueBuffer = NULL;

	//查找缓冲区列表，试图获得一个可以容纳标识符字面值的缓冲
	int count = linked_list_size(*values);
	for (int i = 0; i < count; i++) {
		sBuffer *b = linked_list_nth(*values, i);
		if (buffer_available(b) >= len) {
			valueBuffer = b;
			break;
		}
	}

	if (valueBuffer == NULL) {
		valueBuffer = buffer_new(
		BUFFER_DEFAULT_SIZE > len ? BUFFER_DEFAULT_SIZE : len);
		*values = linked_list_append(*values, valueBuffer);
	}

	//将标识符的字面值写入到缓冲区
	char *value = buffer_write(valueBuffer, buffer_head(buffer), len);
	buffer_write_byte(valueBuffer, '\0');

	//计算哈希值
	long hashcode = 0;

	for (size_t i = 0; i < len; i++) {
		hashcode *= 8;
		hashcode += (value[i] - '0');
	}

	//更新属性
	primitive_set_literal_value(primitive, value);
	primitive_set_value(primitive, hashcode);
	primitive_set_hashcode(primitive, hashcode);
}
