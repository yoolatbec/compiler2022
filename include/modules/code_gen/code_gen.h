/*
 * code_mapping.h
 *
 *  Created on: 2022年6月23日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_CODE_GEN_CODE_GEN_H_
#define INCLUDE_MODULES_CODE_GEN_CODE_GEN_H_

#include <stdio.h>
#include <modules/ir/ir.h>
#include <reserved_word.h>
#include <utils/linked_list.h>

/*
 * 根据中间表示序列生成代码
 */
void code_gen(sLinkedListNode*, const char*);

#endif /* INCLUDE_MODULES_CODE_GEN_CODE_GEN_H_ */
