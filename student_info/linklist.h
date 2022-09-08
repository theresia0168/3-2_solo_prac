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
1. 학생 정보 입력 받기 + 링크리스트 추가
2. 제거
3. 출석번호 순으로 정렬
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

	printf("출석번호를 입력하시오 : ");
	scanf_s("%d", &num);
	printf("이름을 입력하시오 : ");
	scanf_s("%s", name, 10);
	printf("연락처를 입력하시오 : ");
	scanf_s("%s", ph, 15);
	printf("주소를 입력하시오 : ");
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
	printf("출석번호 : %d\n", info->stu_num);
	printf("이름\t : %s\n", info->name);
	printf("연락처\t : %s\n", info->ph_num);
	printf("주소\t : %s\n\n", info->adr);
}

void info_search(STUDENT_LIST* list) {
	int search;
	STUDENT* train = list->head;
	printf("찾으시는 학생의 출석번호를 입력해주세요 : ");
	scanf_s("%d", &search);
	printf("\n");

	printf(" . . . 해당 학생 정보 열람 중 . . . \n\n");
	while (search != train->stu_num) {
		train = train->next;
	}
	info_print(train);
	printf("*-------------------------*\n\n");
}

#endif