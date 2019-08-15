#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int WriteCount = 0;
int ReadCount = 0;
char chip[2];

long long int readqueue[49] = { 0 };
int SameCheck = 0;

int bongbong = 0;		//������ ��ġ�� �бⰡ 10ȸ �̳����� ����Ǵ� Ƚ���� ī��Ʈ�ϴ� ����
int count = 0;

int QueueCount = 0;

char commend[8];
char sector_number[20];
char size[30];

char time1[40];
char time2[40];

long long int LSN = 0;
long long int LPN = 0;
long long int LBN = 0;

char Reding[100];

void main(FILE* trace) {

	int spar;
	int C_Check, SIZE, S_SIZE;

	fopen_s(&trace, "2016021612-LUN0.csv", "r");            //������������� ����. ���� ������ ������� �ű� ����

	if (trace == NULL) {                           //���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");         //�����޼��� ���
		exit(1);                                    //���α׷� ����
	}

	fseek(trace, 0, SEEK_SET);

	while (!feof(trace)) {
		while (fgets(Reding, sizeof(Reding), trace)) {
			strcpy(time1, strtok(Reding, ","));
			strcpy(time2, strtok(NULL, ","));
			strcpy(commend, strtok(NULL, ","));
			strcpy(chip, strtok(NULL, ","));
			strcpy(sector_number, strtok(NULL, ","));
			strcpy(size, strtok(NULL, "\r\n"));
			//printf("�Է¹��� LSN %d\t", CINT3);
			C_Check = atoi(chip);

			//printf("Ĩ ��ȣ %d\n", C_Check);

			LSN = atoll(sector_number);
			LPN = LSN / 16;
			LBN = LPN / 64;

			if (strcmp(commend, "R") == 0) {
				for (int i = 0; i < 50; i++) {
					if (LPN == readqueue[i]) {
						SameCheck = 1;
						//printf("%s\n", commend);
						//printf("%d��° ť : %lld // ���� LSN : %lld\n", i, readqueue[i],LSN);
					}
				}
				if (SameCheck == 1) {
					bongbong++;
					count++;
					SameCheck = 0;
				}
				if (QueueCount == 50) {
					QueueCount = 0;
				}
				readqueue[QueueCount] = LPN;
				QueueCount++;
			}
			
		}
	}

	printf("20�� �̳��� ������ ���Ͱ� �ٽ� �аų� ���� Ƚ�� : %d ȸ \n\n", bongbong);
	printf("%d ȸ ", count);

	fclose(trace);
}