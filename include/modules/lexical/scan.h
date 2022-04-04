/*
 * scan.h
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#ifndef INCLUDE_MODULES_LEXICAL_SCAN_H_
#define INCLUDE_MODULES_LEXICAL_SCAN_H_

#include <utils/linked_list.h>
#include <stdlib.h>
#include <modules/lexical/sm_util_func.h>
#include <modules/lexical/primitive.h>
#include <modules/mm/buffer.h>

typedef struct sScanStatus sScanStatus;

int scan(sBuffer *input_buffer, sSMNode *sm_root,
		sLinkedListNode **primitive_output, sLinkedListNode **primitive_values,
		sScanStatus *scan_status);

#endif /* INCLUDE_MODULES_LEXICAL_SCAN_H_ */
