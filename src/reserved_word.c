/*
 * reserved_word.c
 *
 *  Created on: 2022年3月3日
 *      Author: yoolatbec
 */

#include <reserved_word.h>
#define NULL ((void*)0)

const sReservedWord rw_char =
	{ "char",
	RW_ID_CHAR };

const sReservedWord rw_short =
	{ "short",
	RW_ID_SHORT };

const sReservedWord rw_int =
	{ "int",
	RW_ID_INT };

const sReservedWord rw_long =
	{ "long",
	RW_ID_LONG };

const sReservedWord rw_float =
	{ "float",
	RW_ID_FLOAT };

const sReservedWord rw_double =
	{ "double",
	RW_ID_DOUBLE };

const sReservedWord rw_auto =
	{ "auto",
	RW_ID_AUTO };

const sReservedWord rw_void =
	{ "void",
	RW_ID_VOID };

const sReservedWord rw_unsigned =
	{ "unsigned",
	RW_ID_UNSIGNED };

const sReservedWord rw_signed =
	{ "signed",
	RW_ID_SIGNED };

const sReservedWord rw_static =
	{ "static",
	RW_ID_STATIC };

const sReservedWord rw_const =
	{ "const",
	RW_ID_CONST };

const sReservedWord rw_register =
	{ "register",
	RW_ID_REGISTER };

const sReservedWord rw_extern =
	{ "extern",
	RW_ID_EXTERN };

const sReservedWord rw_global =
	{ "global",
	RW_ID_GLOBAL };

const sReservedWord rw_volatile =
	{ "volatile",
	RW_ID_VOLATILE };

const sReservedWord rw_return =
	{ "return",
	RW_ID_RETURN };

const sReservedWord rw_break =
	{ "break",
	RW_ID_BREAK };

const sReservedWord rw_continue =
	{ "continue",
	RW_ID_CONTINUE };

const sReservedWord rw_goto =
	{ "goto",
	RW_ID_GOTO };

const sReservedWord rw_switch =
	{ "switch",
	RW_ID_SWITCH };

const sReservedWord rw_case =
	{ "case",
	RW_ID_CASE };

const sReservedWord rw_default =
	{ "default",
	RW_ID_DEFAULT };

const sReservedWord rw_if =
	{ "if",
	RW_ID_IF };

const sReservedWord rw_else =
	{ "else",
	RW_ID_ELSE };

const sReservedWord rw_for =
	{ "for",
	RW_ID_FOR };

const sReservedWord rw_while =
	{ "while",
	RW_ID_WHILE };

const sReservedWord rw_do =
	{ "do",
	RW_ID_DO };

const sReservedWord rw_struct =
	{ "struct",
	RW_ID_STRUCT };

const sReservedWord rw_union =
	{ "union",
	RW_ID_UNION };

const sReservedWord rw_enum =
	{ "enum",
	RW_ID_ENUM };

const sReservedWord rw_inline =
	{ "inline",
	RW_ID_INLINE };

const sReservedWord rw__Noreturn =
	{ "_Noreturn",
	RW_ID__NORETURN };

const sReservedWord rw_typedef =
	{ "typedef",
	RW_ID_TYPEDEF };

const sReservedWord rw_sizeof =
	{ "sizeof",
	RW_ID_SIZEOF };

const sReservedWord rw_plus =
	{ "+",
	RW_ID_PLUS };

const sReservedWord rw_minus =
	{ "-",
	RW_ID_MINUS };

const sReservedWord rw_ast =
	{ "*",
	RW_ID_AST };

const sReservedWord rw_percent =
	{ "%",
	RW_ID_PERCENT };

const sReservedWord rw_slash =
	{ "/",
	RW_ID_SLASH };

const sReservedWord rw_backslash =
	{ "\\",
	RW_ID_BACKSLASH };

const sReservedWord rw_logic_and =
	{ "&&",
	RW_ID_LOGIC_AND };

const sReservedWord rw_logic_or =
	{ "||",
	RW_ID_LOGIC_OR };

const sReservedWord rw_logic_not =
	{ "!",
	RW_ID_LOGIC_NOT };

const sReservedWord rw_bitwise_and =
	{ "&",
	RW_ID_BITWISE_AND };

const sReservedWord rw_bitwise_or =
	{ "|",
	RW_ID_BITWISE_OR };

const sReservedWord rw_bitwise_not =
	{ "~",
	RW_ID_BITWISE_NOT };

const sReservedWord rw_bitwise_xor =
	{ "^",
	RW_ID_BITWISE_XOR };

const sReservedWord rw_left_shift =
	{ "<<",
	RW_ID_LEFT_SHIFT };

const sReservedWord rw_right_shift =
	{ ">>",
	RW_ID_RIGHT_SHIFT };

const sReservedWord rw_inc =
	{ "++",
	RW_ID_INC };

const sReservedWord rw_dec =
	{ "--",
	RW_ID_DEC };

const sReservedWord rw_parenthesis_left =
	{ "(",
	RW_ID_PARENTHESIS_LEFT };

const sReservedWord rw_parenthesis_right =
	{ ")",
	RW_ID_PARENTHESIS_RIGHT };

const sReservedWord rw_bracket_left =
	{ "[",
	RW_ID_BRACKET_LEFT };

const sReservedWord rw_bracket_right =
	{ "]",
	RW_ID_BRACKET_RIGHT };

const sReservedWord rw_brace_left =
	{ "{",
	RW_ID_BRACE_LEFT };

const sReservedWord rw_brace_right =
	{ "}",
	RW_ID_BRACE_RIGHT };

const sReservedWord rw_comma =
	{ ",",
	RW_ID_COMMA };

const sReservedWord rw_equal =
	{ "==",
	RW_ID_EQUAL };

const sReservedWord rw_not_equal =
	{ "!=",
	RW_ID_NOT_EQUAL };

const sReservedWord rw_greater_than =
	{ ">",
	RW_ID_GREATER_THAN };

const sReservedWord rw_greater_equal =
	{ ">=",
	RW_ID_GREATER_EQUAL };

const sReservedWord rw_less_than =
	{ "<",
	RW_ID_LESS_THAN };

const sReservedWord rw_less_equal =
	{ "<=",
	RW_ID_LESS_EQUAL };

const sReservedWord rw_question_mark =
	{ "?",
	RW_ID_QUESTION_MARK };

const sReservedWord rw_colon =
	{ ":",
	RW_ID_COLON };

const sReservedWord rw_assign =
	{ "=",
	RW_ID_ASSIGN };

const sReservedWord rw_plus_assign =
	{ "+=",
	RW_ID_PLUS_ASSIGN };

const sReservedWord rw_minus_assign =
	{ "-=",
	RW_ID_MINUS_ASSIGN };

const sReservedWord rw_multiply_assign =
	{ "*=",
	RW_ID_MULTIPLY_ASSIGN };

const sReservedWord rw_divide_assign =
	{ "/=",
	RW_ID_DIVIDE_ASSIGN };

const sReservedWord rw_mod_assign =
	{ "%=",
	RW_ID_MOD_ASSIGN };

const sReservedWord rw_left_shift_assign =
	{ "<<=",
	RW_ID_LEFT_SHIFT };

const sReservedWord rw_right_shift_assign =
	{ ">>=",
	RW_ID_RIGHT_SHIFT_ASSIGN };

const sReservedWord rw_bitwise_and_assign =
	{ "&=",
	RW_ID_BITWISE_AND_ASSIGN };

const sReservedWord rw_bitwise_or_assign =
	{ "|=",
	RW_ID_BITWISE_OR_ASSIGN };

const sReservedWord rw_bitwise_xor_assign =
	{ "^=",
	RW_ID_BITWISE_XOR_ASSIGN };

const sReservedWord rw_semicolon =
	{ ";",
	RW_ID_SEMICOLON };

const sReservedWord rw_dot =
	{ ".",
	RW_ID_DOT };

const sReservedWord rw_member =
	{ "->",
	RW_ID_MEMBER };

const sReservedWord rw_quotation_mark =
	{ "\"",
	RW_ID_QUOTATION_MARK };

const sReservedWord rw_single_quotation_mark =
	{ "\'",
	RW_ID_SINGLE_QUOTATION_MARK };

const sReservedWord *const reserved_words[] =
	{
		&rw_char,
		&rw_short,
		&rw_int,
		&rw_long,
		&rw_float,
		&rw_double,
		&rw_auto,
		&rw_void,
		&rw_unsigned,
		&rw_signed,
		&rw_static,
		&rw_const,
		&rw_register,
		&rw_extern,
		&rw_global,
		&rw_volatile,
		&rw_return,
		&rw_break,
		&rw_continue,
		&rw_goto,
		&rw_switch,
		&rw_case,
		&rw_default,
		&rw_if,
		&rw_else,
		&rw_for,
		&rw_while,
		&rw_do,
		&rw_struct,
		&rw_union,
		&rw_enum,
		&rw_inline,
		&rw__Noreturn,
		&rw_typedef,
		&rw_sizeof,
		&rw_plus,
		&rw_minus,
		&rw_ast,
		&rw_percent,
		&rw_slash,
		&rw_backslash,
		&rw_logic_and,
		&rw_logic_or,
		&rw_logic_not,
		&rw_bitwise_and,
		&rw_bitwise_or,
		&rw_bitwise_not,
		&rw_bitwise_xor,
		&rw_left_shift,
		&rw_right_shift,
		&rw_inc,
		&rw_dec,
		&rw_parenthesis_left,
		&rw_parenthesis_right,
		&rw_bracket_left,
		&rw_bracket_right,
		&rw_brace_left,
		&rw_brace_right,
		&rw_comma,
		&rw_equal,
		&rw_not_equal,
		&rw_greater_than,
		&rw_greater_equal,
		&rw_less_than,
		&rw_less_equal,
		&rw_question_mark,
		&rw_colon,
		&rw_assign,
		&rw_plus_assign,
		&rw_minus_assign,
		&rw_multiply_assign,
		&rw_divide_assign,
		&rw_mod_assign,
		&rw_left_shift_assign,
		&rw_right_shift_assign,
		&rw_bitwise_and_assign,
		&rw_bitwise_or_assign,
		&rw_bitwise_xor_assign,
		&rw_semicolon,
		&rw_dot,
		&rw_member,
		&rw_quotation_mark,
		&rw_single_quotation_mark,
		NULL };
