#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int CINT3;


int WriteCount = 0;
int ReadCount = 0;

int readqueue[9] = { 0 };
int SameCheck = 0;

int bongbong = 0;		//������ ��ġ�� �бⰡ 10ȸ �̳����� ����Ǵ� Ƚ���� ī��Ʈ�ϴ� ����

int QueueCount = 0;

char commend[8];
char sector_number[20];
char size[30];
char chip_number[8];
char time[20];
char ent[2];

long long int LSN = 0;

char Reding[100];

void main(FILE* trace, FILE* User_file) {

	int count;
	int spar;
	int C_Check, SIZE, S_SIZE;

	fopen_s(&trace, "Financial1.spc", "r");            //������������� ����. ���� ������ ������� �ű� ����

	if (trace == NULL) {                           //���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");         //�����޼��� ���
		exit(1);                                    //���α׷� ����
	}
	fopen_s(&User_file, "Chip_10_test2.txt", "a+");				//���� �������� ����. ���� ������ ������� �ű� ����
	if (User_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}

	fseek(trace, 0, SEEK_SET);

	while (!feof(trace)) {
		while (fgets(Reding, sizeof(Reding), trace)) {
			strcpy(chip_number, strtok(Reding, ","));
			strcpy(sector_number, strtok(NULL, ","));
			strcpy(size, strtok(NULL, ","));
			strcpy(commend, strtok(NULL, ","));
			strcpy(time, strtok(NULL, "/n"));

			CINT3 = atoi(sector_number);
			//printf("�Է¹��� LSN %d\t", CINT3);
			C_Check = atoi(chip_number);

			//printf("Ĩ ��ȣ %d\n", C_Check);

			LSN = atoll(sector_number);

			if (C_Check == 10) {

				//printf("Ĩ ��ȣ %d\n", C_Check);
				
				if ((strcmp(commend, "r") == 0)) {
					for (int i = 0; i < 10; i++) {
						if (LSN == readqueue[i]) {
							SameCheck = 1;
							//printf("%d\t%d\n", LSN, readqueue[i]);
						}
					}
						if (SameCheck == 1) {
							bongbong = bongbong + 1;
							SameCheck = 0;
						}
						if (QueueCount == 10) {
							QueueCount = 0;
						}
						readqueue[QueueCount] = LSN;
						QueueCount++;
					ReadCount++;
				}
				else {
					WriteCount++;
				}

					//LPN = LSN / 16;
					//LBN = LPN / 5;

					//itoa(LPN, LPNC, 10);
					//itoa(LBN, LBNC, 10);

				
					//printf("size : %s \n", size);
					//printf("commend : %s \n", commend);

					
				fputs(sector_number, User_file); 
				fputs("\t", User_file);
					fputs(size, User_file);
					fputs("\t", User_file);
					fwrite(&commend, sizeof(commend),1,User_file);
					fwrite("\r\n",sizeof(ent),1,User_file);


					size[0] = '\0';
					commend[0] = '\0';
					sector_number[0] = '\0';
				}
		}
	}

	printf("\n\n �� ���� ���� %dȸ\t �� �б� ���� %d ȸ \n\n", WriteCount,ReadCount);
	printf("10�� �̳��� ������ ���Ͱ� �ٽ� ���� Ƚ�� : %d ȸ \n\n", bongbong);

	fclose(trace);
	fclose(User_file);
}

// Ĩ 1 ��ü���� Ƚ�� = 435222, W �� = 311311