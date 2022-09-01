#include <stdio.h>
#include "linklist.h"

int main(int argc, char* argv[]) {
	int command_num;
	STUDENT* stu = NULL;

	printf("\t\t\t\t\t* ㅡㅡㅡ 학생 정보 관리 시스템 ㅡㅡㅡ *\n");
	while (1) {
		printf("1. 신규 학생 정보 입력\n");
		printf("2. 기존 학생 정보 수정\n");
		printf("3. 기존 학생 정보 삭제\n");
		printf("4. 학생 정보 열람\n");
		printf("5. 프로그램 종료\n");
		printf("$ ");
		scanf_s("%d", &command_num);
		printf("\n");

		command(command_num, stu);
		if (command_num == 5)
			break;
	}

	return 0;
}
