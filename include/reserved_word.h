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

#define RW_ID_CHAR (1)
extern const sReservedWord rw_char;

#define RW_ID_SHORT (2)
extern const sReservedWord rw_short;

#define RW_ID_INT (3)
extern const sReservedWord rw_int;

#define RW_ID_LONG (4)
extern const sReservedWord rw_long;

#define RW_ID_FLOAT (5)
extern const sReservedWord rw_float;

#define RW_ID_DOUBLE (6)
extern const sReservedWord rw_double;

#define RW_ID_AUTO (7)
extern const sReservedWord rw_auto;

#define RW_ID_VOID (8)
extern const sReservedWord rw_void;

#define RW_ID_UNSIGNED (9)
extern const sReservedWord rw_unsigned;

#define RW_ID_SIGNED (10)
extern const sReservedWord rw_signed;

#define RW_ID_STATIC (11)
extern const sReservedWord rw_static;

#define RW_ID_CONST (12)
extern const sReservedWord rw_const;

#define RW_ID_REGISTER (13)
extern const sReservedWord rw_register;

#define RW_ID_EXTERN (14)
extern const sReservedWord rw_extern;

#define RW_ID_GLOBAL (15)
extern const sReservedWord rw_global;

#define RW_ID_VOLATILE (16)
extern const sReservedWord rw_volatile;

#define RW_ID_RETURN (17)
extern const sReservedWord rw_return;

#define RW_ID_BREAK (18)
extern const sReservedWord rw_break;

#define RW_ID_CONTINUE (19)
extern const sReservedWord rw_continue;

#define RW_ID_GOTO (20)
extern const sReservedWord rw_goto;

#define RW_ID_SWITCH (21)
extern const sReservedWord rw_switch;

#define RW_ID_CASE (22)
extern const sReservedWord rw_case;

#define RW_ID_DEFAULT (23)
extern const sReservedWord rw_default;

#define RW_ID_IF (24)
extern const sReservedWord rw_if;

#define RW_ID_ELSE (25)
extern const sReservedWord rw_else;

#define RW_ID_FOR (26)
extern const sReservedWord rw_for;

#define RW_ID_WHILE (27)
extern const sReservedWord rw_while;

#define RW_ID_DO (28)
extern const sReservedWord rw_do;

#define RW_ID_STRUCT (29)
extern const sReservedWord rw_struct;

#define RW_ID_UNION (30)
extern const sReservedWord rw_union;

#define RW_ID_ENUM (31)
extern const sReservedWord rw_enum;

#define RW_ID_INLINE (32)
extern const sReservedWord rw_inline;

#define RW_ID__NORETURN (33)
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

#define RW_ID_INC (52)
extern const sReservedWord rw_inc;

#define RW_ID_DEC (53)
extern const sReservedWord rw_dec;

#define RW_ID_PARENTHESIS_LEFT (54)
extern const sReservedWord rw_parenthesis_left;

#define RW_ID_PARENTHESIS_RIGHT (55)
extern const sReservedWord rw_parenthesis_right;

#define RW_ID_BRACKET_LEFT (56)
extern const sReservedWord rw_bracket_left;

#define RW_ID_BRACKET_RIGHT (57)
extern const sReservedWord rw_bracket_right;

#define RW_ID_BRACE_LEFT (58)
extern const sReservedWord rw_brace_left;

#define RW_ID_BRACE_RIGHT (59)
extern const sReservedWord rw_brace_right;

#define RW_ID_COMMA (60)
extern const sReservedWord rw_comma;

#define RW_ID_EQUAL (61)
extern const sReservedWord rw_equal;

#define RW_ID_NOT_EQUAL (62)
extern const sReservedWord rw_not_equal;

#define RW_ID_GREATER_THAN (63)
extern const sReservedWord rw_greater_than;

#define RW_ID_GREATER_EQUAL (64)
extern const sReservedWord rw_greater_equal;

#define RW_ID_LESS_THAN (65)
extern const sReservedWord rw_less_than;

#define RW_ID_LESS_EQUAL (66)
extern const sReservedWord rw_less_equal;

#define RW_ID_QUESTION_MARK (67)
extern const sReservedWord rw_question_mark;

#define RW_ID_COLON (68)
extern const sReservedWord rw_colon;

#define RW_ID_ASSIGN (69)
extern const sReservedWord rw_assign;

#define RW_ID_PLUS_ASSIGN (70)
extern const sReservedWord rw_plus_assign;

#define RW_ID_MINUS_ASSIGN (71)
extern const sReservedWord rw_minus_assign;

#define RW_ID_MULTIPLY_ASSIGN (72)
extern const sReservedWord rw_multiply_assign;

#define RW_ID_DIVIDE_ASSIGN (73)
extern const sReservedWord rw_divide_assign;

#define RW_ID_MOD_ASSIGN (74)
extern const sReservedWord rw_mode_assign;

#define RW_ID_LEFT_SHIFT_ASSIGN (75)
extern const sReservedWord rw_left_shift_assign;

#define RW_ID_RIGHT_SHIFT_ASSIGN (76)
extern const sReservedWord rw_right_shift_assign;

#define RW_ID_BITWISE_AND_ASSIGN (77)
extern const sReservedWord rw_bitwise_and_assign;

#define RW_ID_BITWISE_OR_ASSIGN (78)
extern const sReservedWord rw_bitwise_or_assign;

#define RW_ID_BITWISE_XOR_ASSIGN (79)
extern const sReservedWord rw_bitwise_xor_assign;

#define RW_ID_SEMICOLON (80)
extern const sReservedWord rw_semicolon;

#define RW_ID_DOT (81)
extern const sReservedWord rw_dot;

#define RW_ID_MEMBER (82)
extern const sReservedWord rw_member;

#define RW_ID_QUOTATION_MARK (83)
extern const sReservedWord rw_quotation_mark;

#define RW_ID_SINGLE_QUOTATION_MARK (84)
extern const sReservedWord rw_single_quotation_mark;

#endif /* INCLUDE_RESERVED_WORD_H_ */
