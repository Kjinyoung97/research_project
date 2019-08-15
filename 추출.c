#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int CINT3;


int WriteCount = 0;
int ReadCount = 0;

int readqueue[9] = { 0 };
int SameCheck = 0;

int bongbong = 0;		//동일한 위치의 읽기가 10회 이내에서 실행되는 횟수를 카운트하는 변수

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

	fopen_s(&trace, "Financial1.spc", "r");            //사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성

	if (trace == NULL) {                           //파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");         //에러메세지 출력
		exit(1);                                    //프로그램 종료
	}
	fopen_s(&User_file, "Chip_10_test2.txt", "a+");				//비디오 이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (User_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
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
			//printf("입력받은 LSN %d\t", CINT3);
			C_Check = atoi(chip_number);

			//printf("칩 번호 %d\n", C_Check);

			LSN = atoll(sector_number);

			if (C_Check == 10) {

				//printf("칩 번호 %d\n", C_Check);
				
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

	printf("\n\n 총 쓰기 연산 %d회\t 총 읽기 연산 %d 회 \n\n", WriteCount,ReadCount);
	printf("10번 이내에 동일한 섹터가 다시 읽힌 횟수 : %d 회 \n\n", bongbong);

	fclose(trace);
	fclose(User_file);
}

// 칩 1 전체쓰기 횟수 = 435222, W 만 = 311311