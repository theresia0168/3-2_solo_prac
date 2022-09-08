#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int stu_num;
	char *name;
	char *ph_num;
	char *adr;
	struct node *next;
}STUDENT;

typedef struct list {
	STUDENT* head;
	STUDENT* tail;
	int list_len;
}STUDENT_LIST;

/*
1. �л� ���� �Է� �ޱ� + ��ũ����Ʈ �߰�
2. ����
3. �⼮��ȣ ������ ����
*/

STUDENT* input() {
	STUDENT* buf = NULL;
	buf = (STUDENT*)malloc(sizeof(STUDENT) * 1);

	int num;
	char* name;
	char* ph;
	char* adr;

	name = (char*)malloc(sizeof(char) * 10);
	ph = (char*)malloc(sizeof(char) * 15);
	adr = (char*)malloc(sizeof(char) * 30);

	printf("�⼮��ȣ�� �Է��Ͻÿ� : ");
	scanf_s("%d", &num);
	printf("�̸��� �Է��Ͻÿ� : ");
	scanf_s("%s", name, 10);
	printf("����ó�� �Է��Ͻÿ� : ");
	scanf_s("%s", ph, 15);
	printf("�ּҸ� �Է��Ͻÿ� : ");
	scanf_s("%s", adr, 30);

	buf->stu_num = num;
	buf->name = name;
	buf->ph_num = ph;
	buf->adr = adr;

	printf("\n");
	return buf;
}

void info_print(STUDENT* info) {
	printf("*-------------------------*\n\n");
	printf("�⼮��ȣ : %d\n", info->stu_num);
	printf("�̸�\t : %s\n", info->name);
	printf("����ó\t : %s\n", info->ph_num);
	printf("�ּ�\t : %s\n\n", info->adr);
}

void info_search(STUDENT_LIST* list) {
	int search;
	STUDENT* train = list->head;
	printf("ã���ô� �л��� �⼮��ȣ�� �Է����ּ��� : ");
	scanf_s("%d", &search);
	printf("\n");

	printf(" . . . �ش� �л� ���� ���� �� . . . \n\n");
	while (search != train->stu_num) {
		train = train->next;
	}
	info_print(train);
	printf("*-------------------------*\n\n");
}

#endif