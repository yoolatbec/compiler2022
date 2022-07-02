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

/*
 * 这些函数用于根据不同的词法单元类型对有限状态机构建不同的路径
 */

int sm_build_identifier_acc_path(sSMNode*);  //构建识别标识符的路径

int sm_build_integer_acc_path(sSMNode*);  //构建识别十进制数字的路径

int sm_build_octal_integer_acc_path(sSMNode*);  //构建识别八进制数字的路径

int sm_build_hexadecimal_integer_acc_path(sSMNode*);  //构建识别十六进制数字的路径

int sm_build_binary_integer_acc_path(sSMNode*);  //构建识别二进制数字的路径

int sm_build_char_acc_path(sSMNode*);  //构建识别字符的路径

int sm_build_string_acc_path(sSMNode*);  //构建识别字符串的路径

int sm_build_blank_ignore_path(sSMNode*);  //构建识别空白符的路径
int sm_build_comment_ignore_path(sSMNode*);  //构建识别注释的路径

int sm_build_input_src_end_path(sSMNode*);  //构建识别文件末尾的路径

#endif /* INCLUDE_MODULES_LEXICAL_SM_UTIL_FUNC_H_ */
