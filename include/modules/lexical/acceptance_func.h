/*
 * acceptance_func.h
 *
 *  Created on: 2022年2月26日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_ACCEPTANCE_FUNC_H_
#define INCLUDE_MODULES_LEXICAL_ACCEPTANCE_FUNC_H_

typedef int (*ACC_FUNC)(char, char*);

/*
 * 接受函数，附加在有限状态机的边上
 * 如果一个输入字符能够被一条边接受函数接受（即返回真）
 * 那么可以通过这条边跳转到另一个状态
 */

int single_char_acc_func(char, char*);  //接受一个指定字符的接受函数
int lower_case_char_acc_func(char, char*);  //接受所有小写字符的接受函数
int higher_case_char_acc_func(char, char*);  //接受所有大写字符的接受函数
int nozero_number_char_acc_func(char, char*);  //接受非0十进制数字的接受函数
int number_char_acc_func(char, char*);  //接受十进制数字的接受函数
int octal_number_char_acc_func(char, char*);  //接受八进制数字的接受函数
int nozero_octal_number_char_acc_func(char, char*);  //接受非0八进制数字的接受函数
int hexadecimal_number_char_acc_func(char, char*);  //接受十六进制数字的接受函数
int binary_number_char_acc_func(char, char*);  //接受二进制数字的接受函数

int given_char_acc_func(char, char*);  //接受多个指定字符的接受函数

int blank_char_acc_func(char, char*);  //接受空白字符的接受函数
int not_blank_char_acc_func(char, char*);  //接受非空白字符的接受函数

int identifier_char_acc_func(char, char*);  //接受数字、字母和下划线的接受函数
int identifier_head_char_acc_func(char, char*);  //接受字母和下划线的接受函数

int any_char_acc_func(char, char*);  //接受任何字符的接受函数

#endif /* INCLUDE_MODULES_LEXICAL_ACCEPTANCE_FUNC_H_ */
