/*
 * sm_util_func.h
 *
 *  Created on: 6 Mar 2022
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_SM_UTIL_FUNC_H_
#define INCLUDE_MODULES_LEXICAL_SM_UTIL_FUNC_H_

#include <modules/lexical/status_machine.h>
#include <modules/lexical/by_effect_func.h>

#define PRIM_ID_IDENTIFIER (100)
int sm_build_identifier_acc_path(sSMNode*);

#define PRIM_ID_INTEGER (101)
#define PRIM_ID_UINT (102)
#define PRIM_ID_LONG (103)
#define PRIM_ID_ULONG (104)
int sm_build_integer_acc_path(sSMNode*);

#define PRIM_ID_OCTAL_INTEGER (105)
#define PRIM_ID_OCTAL_UINT (106)
#define PRIM_ID_OCTAL_LONG (107)
#define PRIM_ID_OCTAL_ULONG (108)
int sm_build_octal_integer_acc_path(sSMNode*);

#define PRIM_ID_HEXADECIMAL_INTEGER (109)
#define PRIM_ID_HEXADECIMAL_UINT (110)
#define PRIM_ID_HEXADECIMAL_LONG (111)
#define PRIM_ID_HEXADECIMAL_ULONG (112)
int sm_build_hexadecimal_integer_acc_path(sSMNode*);

#define PRIM_ID_BINARY_INTEGER (113)
#define PRIM_ID_BINARY_UINT (114)
#define PRIM_ID_BINARY_LONG (115)
#define PRIM_ID_BINARY_ULONG (116)
int sm_build_binary_integer_acc_path(sSMNode*);

#define PRIM_ID_CHAR (117)
int sm_build_char_acc_path();

#define PRIM_ID_STRING (120)
int sm_build_string_acc_path(sSMNode*);

#define PRIM_ID_FLOAT (121)
#define PRIM_ID_DOUBLE (122)
int sm_build_float_acc_path(sSMNode*);

#define PRIM_ID_ZERO (125)

#define PRIM_ID_BLANK_IGNORE (130)
int sm_build_blank_ignore_path();
int sm_build_comment_ignore_path(sSMNode*);

#endif /* INCLUDE_MODULES_LEXICAL_SM_UTIL_FUNC_H_ */
