/*
 * code_gen.c
 *
 *  Created on: 2022年6月23日
 *      Author: yoolatbec
 */

#include <modules/code_gen/code_gen.h>

void cg_init(FILE*);  //初始化文件头部
void cg_new_var(IR*, FILE*);  //为变量分配空间
void cg_load_addr(IR*, FILE*);  //加载变量地址
void cg_load_imme(IR*, FILE*);  //加载立即数
void cg_load(IR*, FILE*);  //加载变量值
void cg_store(IR*, FILE*);  //保存变量值
void cg_goto(IR*, FILE*);  //无条件跳转
void cg_label(IR*, FILE*);  //生成标签
void cg_if(int, IR*, FILE*);  //条件判断
void cg_while(int, IR*, FILE*);  //循环
void cg_arithmetic(IR*, FILE*);  //算术运算
void cg_boolean(IR*, FILE*);  //布尔运算
void cg_end(FILE*);  //文件结尾，添加返回值

void code_gen(sLinkedListNode *irs, const char *path) {
	FILE *file = fopen(path, "w+");

	cg_init(file);

	int condition = 0;
	while (irs != NULL) {
		IR *ir = (IR*) linked_list_first(irs);
		switch (ir->op) {
		case LOAD:
			cg_load(ir, file);
			break;
		case NEW_VAR:
			cg_new_var(ir, file);
			break;
		case LOAD_ADDR:
			cg_load_addr(ir, file);
			break;
		case LOAD_IMME:
			cg_load_imme(ir, file);
			break;
		case LABEL:
			cg_label(ir, file);
			break;
		case GOTO:
			cg_goto(ir, file);
			break;
		case STORE:
			cg_store(ir, file);
			break;
		case RW_ID_IF:
			cg_if(condition, ir, file);
			break;
		case RW_ID_WHILE:
			cg_while(condition, ir, file);
			break;
		case RW_ID_PLUS:
		case RW_ID_MINUS:
		case RW_ID_AST:
		case RW_ID_SLASH:
		case RW_ID_PERCENT:
			cg_arithmetic(ir, file);
			break;
		case RW_ID_EQUAL:
		case RW_ID_NOT_EQUAL:
		case RW_ID_GREATER_THAN:
		case RW_ID_GREATER_EQUAL:
		case RW_ID_LESS_THAN:
		case RW_ID_LESS_EQUAL:
			cg_boolean(ir, file);
			condition = ir->op;
			break;
		}

		irs = linked_list_remove_first(irs);
	}

	cg_end(file);
	fclose(file);
}

void cg_init(FILE *file) {
	fprintf(file, ".code32\n.text\n.global main\nmain:\nmovl %%esp, %%esi\n");
}

void cg_new_var(IR *ir, FILE *file) {
	fprintf(file, "push $0\n");
}

void cg_load_addr(IR *ir, FILE *file) {
	fprintf(file, "push $%d\n", ir->oprand0);
}

void cg_load_imme(IR *ir, FILE *file) {
	fprintf(file, "push $%d\n", ir->oprand0);
}

void cg_load(IR *ir, FILE *file) {
	fprintf(file, "mov $%d, %%ebx\nsub %%esi, %%ebx\nneg %%ebx\nmov (%%ebx), %%eax\npush %%eax\n", ir->oprand0);
}

void cg_store(IR *ir, FILE *file) {
	fprintf(file,
			"pop %%eax\npop %%ebx\nsub %%esi, %%ebx\nneg %%ebx\nmov %%eax, (%%ebx)\n");
}

void cg_label(IR *ir, FILE *file) {
	fprintf(file, "l%d:\n", ir->result);
}

void cg_goto(IR *ir, FILE *file) {
	fprintf(file, "jmp l%d\n", ir->oprand0);
}

void cg_if(int condition, IR *ir, FILE *file) {
	switch (condition) {
	case RW_ID_GREATER_THAN:
		fprintf(file, "jg l%d\n", ir->oprand0);
		break;
	case RW_ID_GREATER_EQUAL:
		fprintf(file, "jge l%d\n", ir->oprand0);
		break;
	case RW_ID_LESS_THAN:
		fprintf(file, "jl l%d\n", ir->oprand0);
		break;
	case RW_ID_LESS_EQUAL:
		fprintf(file, "jle ld\n", ir->oprand0);
		break;
	case RW_ID_EQUAL:
		fprintf(file, "jz l%d\n", ir->oprand0);
		break;
	case RW_ID_NOT_EQUAL:
		fprintf(file, "jnz l%d\n", ir->oprand0);
		break;
	}
}

void cg_while(int condition, IR *ir, FILE *file) {
	switch (condition) {
	case RW_ID_GREATER_THAN:
		fprintf(file, "jg l%d\n", ir->oprand0);
		break;
	case RW_ID_GREATER_EQUAL:
		fprintf(file, "jge l%d\n", ir->oprand0);
		break;
	case RW_ID_LESS_THAN:
		fprintf(file, "jl l%d\n", ir->oprand0);
		break;
	case RW_ID_LESS_EQUAL:
		fprintf(file, "jle l%d\n", ir->oprand0);
		break;
	case RW_ID_EQUAL:
		fprintf(file, "jz l%d\n", ir->oprand0);
		break;
	case RW_ID_NOT_EQUAL:
		fprintf(file, "jnz l%d\n", ir->oprand0);
		break;
	}
}

void cg_arithmetic(IR *ir, FILE *file) {
	fprintf(file, "pop %%ebx\npop %%eax\n");
	switch (ir->op) {
	case RW_ID_PLUS:
		fprintf(file, "add %%ebx, %%eax\n");
		break;
	case RW_ID_MINUS:
		fprintf(file, "sub %%ebx, %%eax\n");
		break;
	case RW_ID_AST:
		fprintf(file, "mul %%ebx\n");
		break;
	case RW_ID_SLASH:
		fprintf(file, "mov $0, %%edx\ndiv %%ebx\n");
		break;
	case RW_ID_PERCENT:
		fprintf(file, "mov $0, %%edx\ndiv %%ebx\nmov %%edx, %%eax\n");
		break;
	}
	fprintf(file, "push %%eax\n");
}

void cg_boolean(IR *ir, FILE *file) {
	fprintf(file, "pop %%eax\npop %%ebx\ncmp %%eax, %%ebx\n");
}

void cg_end(FILE *file) {
	fprintf(file, "mov $0, %%eax\n");
}

