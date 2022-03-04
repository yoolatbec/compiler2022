/*
 * st_utils.h
 *
 *  Created on: 2022年2月27日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_ST_UTILS_H_
#define INCLUDE_MODULES_LEXICAL_ST_UTILS_H_

#include <errcode.h>
#include <modules/lexical/status_machine.h>

#define RESERVED_WORD_NUM_TYPE_IDENTIFER (1 << 1)
char* type_identifier[] = {
		"char",
		"short",
		"int",
		"long",
		"double",
		"float",
		"auto",
		0
};

#define RESERVED_WORD_NUM_VOID_IDENTIFIER (2 << 1)
char* void_identifier[] = {
		"void",
		0
};

#define RESERVED_WORD_NUM_TYPE_MODIFIER (3 << 1)
char* type_modifier[] = {
		"unsigned",
		"signed",
		"static",
		"const",
		"register",
		"extern",
		"global",
		"volatile",
		0
};

#define RESERVED_WORD_NUM_FLOW_CONTROLLER (4 << 1)
char* flow_controller[] = {
		"return",
		"break",
		"continue",
		0
};

#define RESERVED_WORD_NUM_RETURN_STATEMENT (5 << 1)
char* return_statement[] = {
		"return",
		0
};

#define RESERVED_WORD_NUM_UNARY_OPERATOR (6 << 1)
char* unary_operator[] = {
		"-",
		"*",
		"&",
		"++",
		"--",
		"!",
		"~",
		"sizeof",
		0
};

#define RESERVED_WORD_NUM_POST_UNARY_OPERATOR (7 << 1)
char* post_unary_operator[] = {
		"++",
		"--",
		0
};

#define RESERVED_WORD_NUM_BINARY_OPERATOR (8 << 1)
char* binary_operator[] = {
		"+",
		"-",
		"*",
		"/",
		"%",
		".",
		"->",
		"&&",
		"||",
		"&",
		"|",
		"^",
		",",
		"?",
		":",
		">>",
		"<<",
		"+=",
		"-=",
		"*=",
		"/=",
		"%=",
		">>=",
		"<<=",
		"&=",
		"|=",
		"^=",
		"<",
		">",
		"<=",
		">=",
		"==",
		"!=",
		0
};

#define RESERVED_WORD_NUM_FOR_STATEMENT (9 << 1)
char* for_statement[] = {
		"for",
		0
};

#define RESERVED_WORD_NUM_WHILE_STATEMENT (10 << 1)
char* while_statement[] = {
		"while",
		0
};

#define RESERVED_WORD_NUM_IF_STATEMENT (11 << 1)
char* if_statement[] = {
		"if",
		0
};

#define RESERVED_WORD_NUM_ELSE_STATEMENT (12 << 1)
char* else_statement[] = {
		"else",
		0
};

char* switch_statement[] = {
		"switch",
		"case",
		"default",
		0
};

char* bracket_left[] = {
		"[",
		0
};

char* bracket_right[] = {
		"]",
		0
};

char* parenthesis_left[] = {
		"(",
		0
};

char* parenthesis_right[] = {
		")",
		0
};

char* brace_left[] = {
		"{",
		0
};

char* brace_right[] = {
		"}",
		0
};

char* structure_definition[] = {
		"struct",
		0
};

char* enum_definition[] = {
		"enum",
		0
};

char* union_definition[] = {
		"union",
		0
};

int st_build_string_path(sSTNode**);
int st_build_identifier_path(sSTNode**);
int st_build_single_line_comment_path(sSTNode**);

#endif /* INCLUDE_MODULES_LEXICAL_ST_UTILS_H_ */
