#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int i = 0;
char commend[8];
char sector_number[10];
char size[10];
char time[20];

char time2[30];
char time3[20];
char chip[3];

long long int LSN_SAVE,LSN,LSN2;

long long int sector131072[26465];

int I_size;
//long long int write_count[900000];

//int LSN_Count[5429];
char Reding[80];
char count_read_LSN[20];
char count_LSN[15];
char count_count[5];

char Reding2[50];
char commend2[8];
char sector_number2[10];
char size2[10];

void main(FILE* trace, FILE* trace2, FILE* COUNT) {

	fopen_s(&trace, "2016021612-LUN6_131072고유값.csv", "r");

	if (trace == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다1.\n");
		exit(1);
	}


	fopen_s(&trace2, "2016021612-LUN3.csv", "r");

	if (trace2 == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다2.\n");
		exit(1);
	}

	fopen_s(&COUNT, "2016021612-LUN6_131072외_SIZE존재_섹터.txt", "ab+");
	if (COUNT == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다3.\n");
		exit(1);
	}

	while (!feof(trace)) {
		while (fgets(Reding2, sizeof(Reding2), trace)) {
			strcpy(commend2, strtok(Reding2, ","));
			strcpy(size2, strtok(NULL, ","));
			strcpy(sector_number2, strtok(NULL, ","));

			LSN2 = atoll(sector_number2);
			//printf("%s , %lld \n", sector_number2, LSN2);

			sector131072[i] = LSN2;
			//printf("배열에 저장된 섹터 : %lld\n", sector131072[i]);
			i++;
		}
		
	}
	printf("\n\n====================배열 저장 완료=================================\n\n");

	//fseek(trace, 0, SEEK_SET);


	while (!feof(trace2)) {
		while (fgets(Reding, sizeof(Reding), trace2)) {
			strcpy(time2, strtok(Reding, ","));
			strcpy(time3, strtok(NULL, ","));
			strcpy(commend, strtok(NULL, ","));
			strcpy(chip, strtok(NULL, ","));
			strcpy(sector_number, strtok(NULL, ","));
			strcpy(size, strtok(NULL, ","));

		
			I_size = atoi(size);

			if (I_size != 131072) {

				LSN = atoll(sector_number);
				//printf("%lld번째 섹터와 비교연산중 \n", LSN);
				for (int j = 0; j <26465; j++) {
					if (sector131072[j] == LSN) {
						fputs(sector_number, COUNT);
						fputs("\r\n", COUNT);
						//printf("동일섹터 검출 LSN : %lld\n", sector131072[j]);
					}

				}
			}

		}
	}

	fclose(trace);
	fclose(trace2);
	fclose(COUNT);

}