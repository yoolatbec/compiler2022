/*
 * by_effect_func.h
 *
 *  Created on: 6 Mar 2022
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_BY_EFFECT_FUNC_H_
#define INCLUDE_MODULES_LEXICAL_BY_EFFECT_FUNC_H_

typedef void (*BY_EFFECT_FUNC)(char, void*);

void identifier_by_effect_func(char, void*);
void literal_value_by_effect_func(char, void*);
void string_by_effect_func(char, void*);

void char_by_effect_func(char, void*);
void string_end_by_effect_func(char, void*);

void buffer_write_back_by_effect_func(char, void*);

#endif /* INCLUDE_MODULES_LEXICAL_BY_EFFECT_FUNC_H_ */
