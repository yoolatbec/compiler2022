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
	char *str = "1*(1+1)+1";
	size_t size = strlen(str);
#endif

	sBuffer *buffer = buffer_new(4096);
	buffer_write(buffer, str, size);

	sLinkedListNode *primitives = NULL;
	sLinkedListNode *values = NULL;
	sScanStatus *status = NULL;

	scan(buffer, start_node, &primitives, &values, status);

	sGrammar *start_grammar = init_all_grammar();
	sLinkedListNode *irs = deduce(start_grammar, &primitives);

	print_IRs(irs, 1 << 12);

	return 0;
}
