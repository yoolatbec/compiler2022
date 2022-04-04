/*
 * by_effect_func.c
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#include <modules/lexical/by_effect_func.h>
#include <modules/mm/buffer.h>

void identifier_by_effect_func(char c, void *data) {
	sBuffer *buffer = (sBuffer*) data;
	buffer_write_byte(buffer, c);
}

void literal_value_by_effect_func(char c, void *data) {
	sBuffer *buffer = (sBuffer*) data;
	buffer_write_byte(buffer, c);
}

void char_by_effect_func(char c, void *data) {

}

void string_by_effect_func(char c, void *data) {
	sBuffer *buffer = (sBuffer*) data;
	buffer_write_byte(buffer, c);
}

void string_end_by_effect_func(char c, void *data) {
	sBuffer *buffer = (sBuffer*) data;
	buffer_write_byte(buffer, '\0');
}

void buffer_write_back_by_effect_func(char c, void *data) {

}
