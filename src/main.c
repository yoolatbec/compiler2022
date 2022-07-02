/*
 * main.c
 *
 *  Created on: 2022年2月24日
 *      Author: yoolatbec
 */
#define DEBUG
#include <utils/linked_list.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <modules/lexical/sm_util_func.h>
#include <modules/lexical/scan.h>
#include <modules/grammar/deduce.h>
#include <modules/ir/ir.h>

#include <modules/code_gen/code_gen.h>

int main(int argc, char **argv) {

#ifndef DEBUG
	if (argc < 2) {
		puts("usage: dcc file_name");
		return -1;
	}
#endif

	sSMNode *start_node = (sSMNode*) malloc(sizeof(sSMNode));
	sm_build_input_src_end_path(start_node);
	sm_build_identifier_acc_path(start_node);
	sm_build_integer_acc_path(start_node);
	sm_build_octal_integer_acc_path(start_node);
	sm_build_hexadecimal_integer_acc_path(start_node);
	sm_build_binary_integer_acc_path(start_node);
	sm_build_char_acc_path(start_node);
	sm_build_string_acc_path(start_node);
	sm_build_blank_ignore_path(start_node);
	sm_build_comment_ignore_path(start_node);
	int i = 0;
	while (reserved_words[i] != NULL) {
		sm_add_reserved_word(start_node, reserved_words[i]);
		++i;
	}

#ifndef DEBUG
	FILE *file = fopen(argv[1], "r");
	char str[4096];
	size_t size = fread(str, 1, 4096, file);
	fclose(file);
	printf("%ld\n", size);
#else
	char *str = "int a;"
			"int b;"
			"a = 200;"
			"b = a * 5 + 100;"
			"if ( a > 100) {"
			"a = 100;"
			"} else {"
			"b = a;"
			"}"
			"while(a > 10){"
			"a = a - 10;"
			"}";
	size_t size = strlen(str);
#endif

	sBuffer *buffer = buffer_new(4096);
	buffer_write(buffer, str, size);

	sLinkedListNode *primitives = NULL;
	sLinkedListNode *values = NULL;
	sScanStatus *status = NULL;

	scan(buffer, start_node, &primitives, &values, status);

	int s = linked_list_size(primitives);
	for (int i = 0; i < s; i++) {
		sPrimitive *p = linked_list_nth(primitives, i);
		printf("%d: type = %d\n", i + 1, primitive_get_type(p));

	}

	sGrammar *start_grammar = init_all_grammar();
	sLinkedListNode *irs = deduce(start_grammar, &primitives);

	print_IRs(irs, 1 << 12);

	code_gen(irs, "./test.s");

	return 0;
}
