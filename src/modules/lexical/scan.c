/*
 * scan.c
 *
 *  Created on: 2022年3月24日
 *      Author: yoolatbec
 */

#include <modules/lexical/scan.h>
#include <modules/lexical/sm_util_func.h>

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

/*
 * 表示扫描过程的结构（未使用）
 */
struct sScanStatus {
	sLinkedListNode *prev_status;
	size_t line;
	size_t column;
};

/*
 * 从一个缓冲中读取字符串，生成对应的词法单元序列并保存词法单元的字面值
 */
int scan(sBuffer *input_buffer, sSMNode *sm_root, sLinkedListNode **output,
		sLinkedListNode **primitive_values, sScanStatus *scan_status) {

	//初始化变量
	char *str = (char*) buffer_head(input_buffer);  //待扫面字符串
	sBuffer *temp_buffer = buffer_new(4096);  //临时缓冲
	sLinkedListNode *current_status = NULL;  //从当前状态能够跳转到的状态的集合
	sLinkedListNode *prev_status = NULL;  //当前状态集合
	int cursor = 0;  //用于获取识别字符的浮标
	sSMNode *current_node = sm_root;  //当前状态
	prev_status = linked_list_append(NULL, current_node);
	sLinkedListNode *terminators = NULL;  //终止状态集合
	int should_stop = FALSE;

	while (!should_stop) {
		while (prev_status != NULL) {
			//如果当前状态不为空，则计算能够从当前状态跳转到的状态
			sSMNode *node = linked_list_first(prev_status);
			if (node->node_attr != 0) {
				//如果当前状态为终止状态，则添加到终止状态集合
				if (node->node_attr == INPUT_SRC_END) {
					should_stop = TRUE;
				}
				terminators = linked_list_append(terminators, node);
			}

			sSMEdge *edge = node->first_edge;
			while (edge != NULL) {
				if (edge->acc_func(str[cursor], edge->data)) {
					current_status = linked_list_append(current_status,
							edge->target_node);
					if(edge->by_effect){
						edge->by_effect(str[cursor], temp_buffer);
					}
				}

				edge = edge->next;
			}

			prev_status = linked_list_remove_first(prev_status);
		}

		if (current_status == NULL) {
			if (terminators == NULL && !should_stop) {
				//次状态集合为空且不存在终止状态，表明出现错误
				//should throw an exception
			}

			//根据终止状态集合中的第一个状态构建词法单元
			sSMNode *s = (sSMNode*) linked_list_first(terminators);
			if (s->node_attr != PRIM_ID_BLANK_IGNORE) {
				sPrimitive *primitive = primitive_new_with_type(s->node_attr);
				*output = linked_list_append(*output, primitive);

				if(s->action){
					s->action(primitive, primitive_values, temp_buffer);
				}
			}

			buffer_clear(temp_buffer);

			prev_status = linked_list_append(prev_status, sm_root);
		} else {
			//次状态集合不为空，继续扫描
			prev_status = current_status;
			current_status = NULL;
			cursor++;
		}

		terminators = linked_list_clear(terminators);
	}

	return SUCCESS;
}
