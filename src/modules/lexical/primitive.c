/*
 * primitive.c
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#include <modules/lexical/primitive.h>

struct sPrimitive {
	int primitive_type;
	char *literal_value;
	long hashcode;
};

sPrimitive* primitive_new_with_type(int type) {
	sPrimitive *primitive = (sPrimitive*) malloc(sizeof(sPrimitive));
	primitive->primitive_type = type;
	return primitive;
}

void primitive_set_literal_value(sPrimitive *primitive, char *value) {
	primitive->literal_value = value;
}

void primitive_destroy(sPrimitive *primitive) {
	free(primitive);
}

int primitive_get_type(sPrimitive *primitive) {
	return primitive->primitive_type;
}
