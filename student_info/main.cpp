#include <stdio.h>
#include "linklist.h"

int main(int argc, char* argv[]) {
	int command_num;
	STUDENT_LIST* student = NULL;
	STUDENT* buf = NULL;
	
	student = (STUDENT_LIST*)malloc(sizeof(STUDENT) * 1);
	student->list_len = 0;

	printf("\t\t\t\t\t***************************************\n");
	printf("\t\t\t\t\t* �ѤѤ� �л� ���� ���� �ý��� �ѤѤ� *\n");
	printf("\t\t\t\t\t***************************************\n\n");
	while (1) {
		printf("1. �ű� �л� ���� �Է�\n");
		printf("2. ���� �л� ���� ����\n");
		printf("3. ���� �л� ���� ����\n");
		printf("4. ��ü �л� ���� ����\n");
		printf("5. �л� ���� �˻� ����\n");
		printf("6. ���α׷� ����\n");
		printf("$ ");
		scanf_s("%d", &command_num);
		printf("\n");

		switch (command_num) {
		case 1:	// �л� ���� �Է� �� �⼮��ȣ �� ����
		{
			int count = 1;
			STUDENT* buf = NULL;
			buf = (STUDENT*)malloc(sizeof(STUDENT) * 1);
			buf = input();
			if (student->list_len == 0) {
				student->head = buf;
				student->tail = student->head;
				student->list_len = 1;
			}	// �ű� �л� ���� �Է� �ޱ�
			else {	// �⼮��ȣ �� ���� �ܰ�
				STUDENT* train = NULL;
				train = (STUDENT*)malloc(sizeof(STUDENT) * 1);
				STUDENT* tmp = NULL;
				train = student->head;	// �ӽ� ��� train�� ���Ḯ��Ʈ�� head�� �Ҵ�

				while (1) {
					if (train->stu_num > buf->stu_num) {	// train�� �⼮��ȣ�� ���� �Է� ���� �⼮��ȣ���� ũ�� ��ġ�� �ٲ۴�
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
			printf("�����Ϸ��� �л��� �⼮��ȣ�� �Է����ּ��� : ");
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
			printf("3. ���� �л� ���� ����\n\n");
			int num;
			printf("�����Ϸ��� �л��� �⼮��ȣ�� �Է��ϼ��� : ");
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
			printf(" . . .  ��ü �л� ���� ���� �� . . . \n\n");

			printf("��ü �л� �� : %d\n\n", student->list_len);
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
			printf(" . . . �л� ���� ���� �ý����� �����մϴ�\n");
			break;
		}
		if (command_num == 6)
			break;
	}
	free(student);

	return 0;
}