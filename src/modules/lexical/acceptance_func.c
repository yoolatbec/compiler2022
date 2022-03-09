/*
 * acceptance_func.c
 *
 *  Created on: 2022年2月26日
 *      Author: yoolatbec
 */

#include <modules/lexical/acceptance_func.h>

#define NULL (0)

#define FALSE (0)
#define TRUE (!FALSE)

int single_char_acc_func(char c, char *str) {
	return c == (char)str;
}

int lower_case_char_acc_func(char c, char *str) {
	return c >= 'a' && c <= 'z';
}

int higher_case_char_acc_func(char c, char *str) {
	return c >= 'A' && c <= 'Z';
}

int nozero_number_char_acc_func(char c, char *str) {
	return c > '0' && c <= '9';
}

int number_char_acc_func(char c, char *str) {
	return c >= '0' && c <= '9';
}

int nozero_octal_number_char_acc_func(char c, char *str) {
	return c > '0' && c <= '7';
}

int octal_number_char_acc_func(char c, char *str) {
	return c >= '0' && c <= '7';
}

int hexadecimal_number_char_acc_func(char c, char *str) {
	return (c >= '0' && c <= '9') || given_char_acc_func(c, "aAbBcCdDeEfF");
}

int binary_number_char_acc_func(char c, char *str) {
	return c == '0' || c == '1';
}

int blank_char_acc_func(char c, char *str) {
	return c == ' ' || c == '\n' || c == '\t';
}

int not_blank_char_acc_func(char c, char *str) {
	return !blank_char_acc_func(c, str);
}

int identifier_char_acc_func(char c, char *str) {
	return lower_case_char_acc_func(c, NULL)
		|| higher_case_char_acc_func(c, NULL) || number_char_acc_func(c, NULL)
		|| single_char_acc_func(c, "_");
}

int identifier_head_char_acc_func(char c, char *str) {
	return lower_case_char_acc_func(c, NULL)
		|| higher_case_char_acc_func(c, NULL) || single_char_acc_func(c, "_");
}

int any_char_acc_func(char c, char *str) {
	if(str != NULL){
		int cursor = 0;
		while (str[cursor] != '\0') {
			if (c == str[cursor]) {
				return FALSE;
			}

			cursor++;
		}
	}

	return TRUE;
}

int non_blank_char_acc_func(char c, char *str) {
	return !blank_char_acc_func(c, str);
}

int given_char_acc_func(char c, char *str) {
	if(str != NULL){
		int cursor = 0;
		while (str[cursor] != '\0') {
			if (c == str[cursor]) {
				return TRUE;
			}

			++cursor;
		}
	}

	return FALSE;
}
