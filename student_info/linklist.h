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
	struct node* head;
	struct node* tail;
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

	return buf;
}

void new_node() {

}

void command(int c, STUDENT *info) {
	switch (c) {
		case 1:
			info = input();
			break;
		case 2:
			printf("2. 기존 학생 정보 수정\n\n");
			break;
		case 3:
			printf("3. 기존 학생 정보 삭제\n\n");
			break;
		case 4:
			printf("4. 학생 정보 열람\n\n");
			break;
		case 5:
			printf("ㅡㅡㅡ학생 정보 관리 시스템을 종료합니다\n");
			break;
	}
}

void info_print(STUDENT *info) {
	printf("출석번호 : %d\n", info->stu_num);
	printf("이름 : %s\n", info->name);
	printf("연락처 : %s\n", info->ph_num);
	printf("주소 : %s\n", info->adr);
}

#endif
