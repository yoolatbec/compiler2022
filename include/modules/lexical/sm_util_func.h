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

int sm_build_identifier_acc_path(sSMNode*);

int sm_build_integer_acc_path(sSMNode*);

int sm_build_octal_integer_acc_path(sSMNode*);

int sm_build_hexadecimal_integer_acc_path(sSMNode*);

int sm_build_binary_integer_acc_path(sSMNode*);

int sm_build_char_acc_path(sSMNode*);

int sm_build_string_acc_path(sSMNode*);

//int sm_build_float_acc_path(sSMNode*);

int sm_build_blank_ignore_path(sSMNode*);
int sm_build_comment_ignore_path(sSMNode*);

int sm_build_input_src_end_path(sSMNode*);

#endif /* INCLUDE_MODULES_LEXICAL_SM_UTIL_FUNC_H_ */
