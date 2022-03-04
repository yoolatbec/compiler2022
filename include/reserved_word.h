/*
 * reserved_word.h
 *
 *  Created on: 2022年3月3日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_RESERVED_WORD_H_
#define INCLUDE_RESERVED_WORD_H_

typedef struct sReservedWord {
	const char *value;
	int id;
} sReservedWord;

#define RW_ID_TYPE_IDENTIFIER_CHAR (1)
extern const sReservedWord rw_char;

#define RW_ID_TYPE_IDENTIFIER_SHORT (2)
extern const sReservedWord rw_short;

#define RW_ID_TYPE_IDENTIFIER_INT (3)
extern const sReservedWord rw_int;

#define RW_ID_TYPE_IDENTIFIER_LONG (4)
extern const sReservedWord rw_long;

#define RW_ID_TYPE_IDENTIFIER_FLOAT (5)
extern const sReservedWord rw_float;

#define RW_ID_TYPE_IDENTIFIER_DOUBLE (6)
extern const sReservedWord rw_double;

#define RW_ID_TYPE_IDENTIFIER_AUTO (7)
extern const sReservedWord rw_auto;

#define RW_ID_TYPE_IDENTIFIER_VOID (8)
extern const sReservedWord rw_void;

#define RW_ID_TYPE_MODIFIER_UNSIGNED (9)
extern const sReservedWord rw_unsigned;

#define RW_ID_TYPE_MODIFIER_SIGNED (10)
extern const sReservedWord rw_signed;

#define RW_ID_TYPE_MODIFIER_STATIC (11)
extern const sReservedWord rw_static;

#define RW_ID_TYPE_MODIFIER_CONST (12)
extern const sReservedWord rw_const;

#define RW_ID_TYPE_MODIFIER_REGISTER (13)
extern const sReservedWord rw_register;

#define RW_ID_TYPE_MODIFIER_EXTERN (14)
extern const sReservedWord rw_extern;

#define RW_ID_TYPE_MODIFIER_GLOBAL (15)
extern const sReservedWord rw_global;

#define RW_ID_TYPE_MODIFIER_VOLATILE (16)
extern const sReservedWord rw_volatile;

#define RW_ID_FLOW_CONTROL_RETURN (17)
extern const sReservedWord rw_return;

#define RW_ID_FLOW_CONTROL_BREAK (18)
extern const sReservedWord rw_break;

#define RW_ID_FLOW_CONTROL_CONTINUE (19)
extern const sReservedWord rw_continue;

#define RW_ID_FLOW_CONTROL_GOTO (20)
extern const sReservedWord rw_goto;

#define RW_ID_FLOW_CONTROL_SWITCH (21)
extern const sReservedWord rw_switch;

#define RW_ID_FLOW_CONTROL_CASE (22)
extern const sReservedWord rw_case;

#define RW_ID_FLOW_CONTROL_DEFAULT (23)
extern const sReservedWord rw_default;

#define RW_ID_FLOW_CONTROL_IF (24)
extern const sReservedWord rw_if;

#define RW_ID_FLOW_CONTROL_ELSE (25)
extern const sReservedWord rw_else;

#define RW_ID_FLOW_CONTROL_FOR (26)
extern const sReservedWord rw_for;

#define RW_ID_FLOW_CONTROL_WHILE (27)
extern const sReservedWord rw_while;

#define RW_ID_FLOW_CONTROL_DO (28)
extern const sReservedWord rw_do;

#define RW_ID_NEW_TYPE_DEF_STRUCT (29)
extern const sReservedWord rw_struct;

#define RW_ID_NEW_TYPE_DEF_UNION (30)
extern const sReservedWord rw_union;

#define RW_ID_NEW_TYPE_DEF_ENUM (31)
extern const sReservedWord rw_enum;

#define RW_ID_FUNC_MODIFIER_INLINE (32)
extern const sReservedWord rw_inline;

#define RW_ID_FUNC_MODIFIER__NORETURN (33)
extern const sReservedWord rw__Noreturn;

#define RW_ID_TYPEDEF (34)
extern const sReservedWord rw_typedef;

#define RW_ID_SIZEOF (35)
extern const sReservedWord rw_sizeof;

#define RW_ID_PLUS (36)
extern const sReservedWord rw_plus;

#define RW_ID_MINUS (37)
extern const sReservedWord rw_minus;

#define RW_ID_AST (38)
extern const sReservedWord rw_ast;

#define RW_ID_PERCENT (39)
extern const sReservedWord rw_percent;

#define RW_ID_SLASH (40)
extern const sReservedWord rw_slash;

#define RW_ID_BACKSLASH (41)
extern const sReservedWord rw_backslash;

#define RW_ID_LOGIC_AND (42)
extern const sReservedWord rw_logic_and;

#define RW_ID_LOGIC_OR (43)
extern const sReservedWord rw_logic_or;

#define RW_ID_LOGIC_NOT (44)
extern const sReservedWord rw_logic_not;

#define RW_ID_BITWISE_AND (45)
extern const sReservedWord rw_bitwise_and;

#define RW_ID_BITWISE_OR (46)
extern const sReservedWord rw_bitwise_or;

#define RW_ID_BITWISE_NOT (47)
extern const sReservedWord rw_bitwise_not;

#define RW_ID_BITWISE_XOR (48)
extern const sReservedWord rw_bitwise_xor;

#define RW_ID_LEFT_SHIFT (50)
extern const sReservedWord rw_left_shift;

#define RW_ID_RIGHT_SHIFT (51)
extern const sReservedWord rw_right_shift;


#endif /* INCLUDE_RESERVED_WORD_H_ */
