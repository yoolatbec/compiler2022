/*
 * primitive.c
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#include <modules/lexical/primitive.h>
#include <stdlib.h>

struct sPrimitive {
	int primitive_type;  //词法单元类型（类型见reserved_word.h）
	char *literal_value;  //字面值
	long hashcode;  //哈希值，用于快速查找
	long value;  //值
};

sPrimitive* primitive_new_with_type(int type) {
	sPrimitive *primitive = (sPrimitive*) malloc(sizeof(sPrimitive));
	primitive->primitive_type = type;
	primitive->literal_value = NULL;
	primitive->hashcode = 0;
	primitive->value = 0;
	return primitive;
}

void primitive_set_literal_value(sPrimitive *primitive, char *value) {
	primitive->literal_value = value;
}

char* primitive_get_literal_value(sPrimitive *primitive) {
	return primitive->literal_value;
}

void primitive_destroy(sPrimitive *primitive) {
	free(primitive);
}

void primitive_set_value(sPrimitive *primitive, long value) {
	primitive->value = value;
}

long primitive_get_value(sPrimitive *primitive) {
	return primitive->value;
}

int primitive_get_type(sPrimitive *primitive) {
	return primitive->primitive_type;
}

void primitive_set_hashcode(sPrimitive *primitive, long hashcode) {
	primitive->hashcode = hashcode;
}

long primitive_get_hashcode(sPrimitive *primitive) {
	return primitive->hashcode;
}
