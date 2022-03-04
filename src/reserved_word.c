/*
 * reserved_word.c
 *
 *  Created on: 2022年3月3日
 *      Author: yoolatbec
 */


#include <reserved_word.h>

const sReservedWord rw_char = {
		"char",
		RW_ID_TYPE_IDENTIFIER_CHAR
};

const sReservedWord rw_short = {
		"short",
		RW_ID_TYPE_IDENTIFIER_SHORT
};

const sReservedWord rw_int = {
		"int",
		RW_ID_TYPE_IDENTIFIER_INT
};

const sReservedWord rw_long = {
		"long",
		RW_ID_TYPE_IDENTIFIER_LONG
};

const sReservedWord rw_float = {
		"float",
		RW_ID_TYPE_IDENTIFIER_FLOAT
};

const sReservedWord rw_doduble = {
		"double",
		RW_ID_TYPE_IDENTIFIER_DOUBLE
};

const sReservedWord rw_auto = {
		"auto",
		RW_ID_TYPE_IDENTIFIER_AUTO
};

const sReservedWord rw_void = {
		"void",
		RW_ID_TYPE_IDENTIFIER_VOID
};

const sReservedWord rw_unsigned = {
		"unsigned",
		RW_ID_TYPE_MODIFIER_UNSIGNED
};

const sReservedWord rw_signed = {
		"signed",
		RW_ID_TYPE_MODIFIER_SIGNED
};

const sReservedWord rw_static = {
		"static",
		RW_ID_TYPE_MODIFIER_STATIC
};

const sReservedWord rw_const = {
	"const",
	RW_ID_TYPE_MODIFIER_CONST
};

const sReservedWord rw_register = {
		"register",
		RW_ID_TYPE_MODIFIER_REGISTER
};

const sReservedWord rw_extern = {
		"extern",
		RW_ID_TYPE_MODIFIER_EXTERN
};

const sReservedWord rw_global = {
		"global",
		RW_ID_TYPE_MODIFIER_GLOBAL
};

const sReservedWord rw_volatile = {
		"volatile",
		RW_ID_TYPE_MODIFIER_VOLATILE
};

const sReservedWord rw_return = {
		"return",
		RW_ID_FLOW_CONTROL_RETURN
};

const sReservedWord rw_break = {
		"break",
		RW_ID_FLOW_CONTROL_BREAK
};

const sReservedWord rw_continue = {
		"continue",
		RW_ID_FLOW_CONTROL_CONTINUE
};

const sReservedWord rw_goto = {
		"goto",
		RW_ID_FLOW_CONTROL_GOTO
};

const sReservedWord rw_switch = {
		"switch",
		RW_ID_FLOW_CONTROL_SWITCH
};

const sReservedWord rw_case = {
		"case",
		RW_ID_FLOW_CONTROL_CASE
};

const sReservedWord rw_default = {
		"default",
		RW_ID_FLOW_CONTROL_DEFAULT
};

const sReservedWord rw_if = {
		"if",
		RW_ID_FLOW_CONTROL_IF
};

const sReservedWord rw_else = {
		"else",
		RW_ID_FLOW_CONTROL_ELSE
};

const sReservedWord rw_for = {
		"for",
		RW_ID_FLOW_CONTROL_FOR
};

const sReservedWord rw_while = {
		"while",
		RW_ID_FLOW_CONTROL_WHILE
};

const sReservedWord rw_do = {
		"do",
		RW_ID_FLOW_CONTROL_DO
};

const sReservedWord rw_struct = {
		"struct",
		RW_ID_NEW_TYPE_DEF_STRUCT
};

const sReservedWord rw_union = {
		"union",
		RW_ID_NEW_TYPE_DEF_UNION
};

const sReservedWord rw_enum = {
		"enum",
		RW_ID_NEW_TYPE_DEF_ENUM
};

const sReservedWord rw_inline = {
		"inline",
		RW_ID_FUNC_MODIFIER_INLINE
};

const sReservedWord rw__Noreturn = {
		"_Noreturn",
		RW_ID_FUNC_MODIFIER__NORETURN
};

const sReservedWord rw_typedef = {
		"typedef",
		RW_ID_TYPEDEF
};

const sReservedWord rw_sizeof = {
		"sizeof",
		RW_ID_SIZEOF
};

const sReservedWord rw_plus = {
		"+",
		RW_ID_PLUS
};

const sReservedWord rw_minus = {
		"-",
		RW_ID_MINUS
};

const sReservedWord rw_ast = {
		"*",
		RW_ID_AST
};

const sReservedWord rw_percent = {
		"%",
		RW_ID_PERCENT
};

const sReservedWord rw_slash = {
		"/",
		RW_ID_SLASH
};

const sReservedWord rw_backslash = {
		"\\",
		RW_ID_BACKSLASH
};

const sReservedWord rw_logic_and = {
		"&&",
		RW_ID_LOGIC_AND
};


