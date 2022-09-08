#include <stdio.h>
#include "linklist.h"

int main(int argc, char* argv[]) {
	int command_num;
	STUDENT_LIST* student = NULL;
	STUDENT* buf = NULL;
	
	student = (STUDENT_LIST*)malloc(sizeof(STUDENT) * 1);
	student->list_len = 0;

	printf("\t\t\t\t\t***************************************\n");
	printf("\t\t\t\t\t* ㅡㅡㅡ 학생 정보 관리 시스템 ㅡㅡㅡ *\n");
	printf("\t\t\t\t\t***************************************\n\n");
	while (1) {
		printf("1. 신규 학생 정보 입력\n");
		printf("2. 기존 학생 정보 수정\n");
		printf("3. 기존 학생 정보 삭제\n");
		printf("4. 전체 학생 정보 열람\n");
		printf("5. 학생 정보 검색 열람\n");
		printf("6. 프로그램 종료\n");
		printf("$ ");
		scanf_s("%d", &command_num);
		printf("\n");

		switch (command_num) {
		case 1:	// 학생 정보 입력 및 출석번호 순 정렬
		{
			int count = 1;
			STUDENT* buf = NULL;
			buf = (STUDENT*)malloc(sizeof(STUDENT) * 1);
			buf = input();
			if (student->list_len == 0) {
				student->head = buf;
				student->tail = student->head;
				student->list_len = 1;
			}	// 신규 학생 정보 입력 받기
			else {	// 출석번호 순 정렬 단계
				STUDENT* train = NULL;
				train = (STUDENT*)malloc(sizeof(STUDENT) * 1);
				STUDENT* tmp = NULL;
				train = student->head;	// 임시 노드 train에 연결리스트의 head를 할당

				while (1) {
					if (train->stu_num > buf->stu_num) {	// train의 출석번호가 현재 입력 받은 출석번호보다 크면 위치를 바꾼다
						if (train == student->head) {
							buf->next = student->head;
							student->head = buf;
						}
						else {
							tmp->next = buf;
							buf->next = train;
							break;
						}
					}
					else {
						if (count != student->list_len) {
							tmp = train;
							train = train->next;
						}
						else {
							train->next = buf;
							break;
						}
					}
					count++;
				}
				student->list_len++;
			}
		}
		break;
		case 2: {
			int num;
			printf("수정하려는 학생의 출석번호를 입력해주세요 : ");
			scanf_s("%d", &num);
			printf("\n");

			STUDENT* train = student->head;
			while (train->stu_num != num) {
				train = train->next;
			}
			*train = *input();
			
			break;
		}
			
		case 3:
		{
			printf("3. 기존 학생 정보 삭제\n\n");
			int num;
			printf("삭제하려는 학생의 출석번호를 입력하세요 : ");
			scanf_s("%d", &num);
			printf("\n");

			STUDENT* train = student->head;
			STUDENT* tmp = NULL;
			while (train->next->stu_num != num) {
				train = train->next;
			}
			tmp = train->next->next;
			free(train->next);
			train->next = tmp;
			student->list_len--;
			break;
		}
		case 4:
		{
			STUDENT* train = student->head;
			printf(" . . .  전체 학생 정보 열람 중 . . . \n\n");

			printf("전체 학생 수 : %d\n\n", student->list_len);
			for (int i = 0; i < student->list_len; i++) {
				info_print(train);
				train = train->next;
			}printf("*-------------------------*\n\n");
			break;
		}
		case 5:
		{
			info_search(student);
			break;
		}
		case 6:
			printf(" . . . 학생 정보 관리 시스템을 종료합니다\n");
			break;
		}
		if (command_num == 6)
			break;
	}
	free(student);

	return 0;
}