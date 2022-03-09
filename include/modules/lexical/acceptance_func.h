/*
 * acceptance_func.h
 *
 *  Created on: 2022年2月26日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_ACCEPTANCE_FUNC_H_
#define INCLUDE_MODULES_LEXICAL_ACCEPTANCE_FUNC_H_

typedef int (*ACC_FUNC)(char, char*);

int single_char_acc_func(char, char*);
int lower_case_char_acc_func(char, char*);
int higher_case_char_acc_func(char, char*);
int nozero_number_char_acc_func(char, char*);
int number_char_acc_func(char, char*);
int octal_number_char_acc_func(char, char*);
int nozero_octal_number_char_acc_func(char, char*);
int hexadecimal_number_char_acc_func(char, char*);
int binary_number_char_acc_func(char, char*);

int given_char_acc_func(char, char*);

int blank_char_acc_func(char, char*);
int not_blank_char_acc_func(char, char*);

int identifier_char_acc_func(char, char*);
int identifier_head_char_acc_func(char, char*);

/*
 * Accept any characters, except those that are given
 * in the string as the second argument.
 */
int any_char_acc_func(char, char*);

#endif /* INCLUDE_MODULES_LEXICAL_ACCEPTANCE_FUNC_H_ */
