#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int WriteCount = 0;
int ReadCount = 0;

long long int readqueue[9] = { 0 };
int SameCheck = 0;

int bongbong = 0;		//동일한 위치의 읽기가 10회 이내에서 실행되는 횟수를 카운트하는 변수

int QueueCount = 0;

char commend[2];
char sector_number[22];
char size[20];
char chip[2];
char start_time[22];
char time[10];
char ent[2];
char LPNC[7];
char LBNC[7];

int count2 = 0;
long long int LSN = 0;
int LPN = 0;
int LBN = 0;

char Reding[200];

void main(FILE* trace, FILE* User_file) {

	int count;
	int spar;
	int C_Check, SIZE, S_SIZE;
	int q = 0;
	int o = 0;
	int w = 0;

	strcpy(ent, "\n");

	fopen_s(&trace, "2016021612-LUN0.csv", "r");            //사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성

	if (trace == NULL) {                           //파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");         //에러메세지 출력
		exit(1);                                    //프로그램 종료
	}
	fopen_s(&User_file, "2016021612-LUN0_modify.txt", "ab+");				//비디오 이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (User_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}

	fseek(trace, 0, SEEK_SET);

	while (!feof(trace)) {
		while (fgets(Reding, sizeof(Reding), trace)) {
			strcpy(start_time, strtok(Reding, ","));
			strcpy(time, strtok(NULL, ","));
			strcpy(commend, strtok(NULL, ","));
			strcpy(chip, strtok(NULL, ","));
			strcpy(sector_number, strtok(NULL, ","));
			strcpy(size, strtok(NULL, "/n"));

			count2++;

			
			LSN = atoll(sector_number);
			SIZE = atoi(size);
			//printf("현재 LSN %llu\t", LSN);

			if ((strcmp(commend, "R") == 0)) {
				for (int i = 0; i < 10; i++) {
					//printf("%d 번째 큐 값 출력 %llu\n",i, readqueue[i]);
					if (LSN == readqueue[i]) {
						SameCheck = 1;
						//printf("동일한 LSN 발견 %d번째 큐 , %llu  = %llu\n", i, readqueue[i], LSN);
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

			LPN = LSN / 16;
			LBN = LPN / 5;


			//itoa(LPN, LPNC, 10);
			//itoa(LBN, LBNC, 10);
			


			fwrite(&sector_number, sizeof(sector_number), 1, User_file);
			fwrite(&commend, sizeof(commend), 1, User_file);
			fwrite(&size, sizeof(size), 1, User_file);
			//fwrite(&LPNC, sizeof(LPNC), 1, User_file);
			//fwrite(&LBNC, sizeof(LBNC), 1, User_file);
			fwrite("\r\n", sizeof(ent), 1, User_file);
			//printf("%d 번행 복사 완료 \n", count2);

			size[0] = '\0';
			start_time[0] = '\0';
			time[0] = '\0';
			commend[0] = '\0';
			chip[0] = '\0';
			sector_number[0] = '\0';

		}
	}

	printf("\n\n 총 쓰기 연산 %d회\t 총 읽기 연산 %d 회 \n\n", WriteCount, ReadCount);
	printf("10번 이내에 동일한 섹터가 다시 읽힌 횟수 : %d 회 \n\n", bongbong);

	fclose(trace);
	fclose(User_file);
}

// 칩 1 전체쓰기 횟수 = 435222, W 만 = 311311