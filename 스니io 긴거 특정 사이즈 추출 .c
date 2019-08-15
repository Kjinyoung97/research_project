#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

char commend[2];
char sector_number[40];
char size[10];
char size_sector[10];
char chip[2];

int SIZE;

int count_commend = 0;
int read_count = 0;
int write_count = 0;

char time1[40];
char time2[40];
char time3[30];
char time4[30];

int check[10] = { 512,1024,2048,4096,8192,16384,12288,32768,131072 };
int count[10] = { 0 };

int CINT3, C_Check, LSN;

char Reding1[200];


char change_commend[2];
int commend_count;

void main(FILE* trace, FILE* COUNT,FILE* COUNT2) {

	fopen_s(&trace, "2016021612-LUN3.csv", "r");

	if (trace == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	fopen_s(&COUNT, "2016021612-LUN3_32768_WRITE.txt", "ab+");
	if (COUNT == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	fopen_s(&COUNT2, "2016021612-LUN6_32768_READ.txt", "ab+");
	if (COUNT == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}


	//fseek(trace, 0, SEEK_SET);


	while (!feof(trace)) {
		while (fgets(Reding1, sizeof(Reding1), trace)) {
			strcpy(time1, strtok(Reding1, ","));
			strcpy(time2, strtok(NULL, ","));
			strcpy(commend, strtok(NULL, ","));
			strcpy(chip, strtok(NULL, ","));
			strcpy(sector_number, strtok(NULL, ","));
			strcpy(size, strtok(NULL, "\r\n"));

			LSN = atoi(sector_number);
			commend_count = atoi(commend);

			/*if (commend_count % 2 == 0) {
				change_commend[0] = 'r';
			}
			else if (commend_count % 2 == 1) {
				change_commend[0] = 'w';
			}*/

			SIZE = atoi(size);
			//LSN_SAVE = LSN;

			//for (int i = 0; i < 10; i++) {

			if (SIZE == 32768 ) {

				if (strcmp(commend, "W") == 0) {
					fputs(commend, COUNT);
					fputs(",", COUNT);
					fputs(size, COUNT);
					fputs(",", COUNT);
					fputs(sector_number, COUNT);
					fputs(",", COUNT);
					fputs(time1, COUNT);
					fputs("\r\n", COUNT);

					write_count++;

				}
				else {

					fputs(commend, COUNT2);
					fputs(",", COUNT2);
					fputs(size, COUNT2);
					fputs(",", COUNT2);
					fputs(sector_number, COUNT2);
					fputs(",", COUNT2);
					fputs(time1, COUNT2);
					fputs("\r\n", COUNT2);

					read_count++;
				}
			


					//count[i] = count[i] + 1;
				}
			//}
			//count_commend++;
		}
	}
	printf("32768의 read 개수 : %d\n", read_count);
	printf("32768B의 write 개수 : %d\n\n", write_count);
	fprintf(COUNT,"32768B의 read 개수 : %d", read_count);
	fprintf(COUNT, "32768B의 wirte 개수 : %d", write_count);
	//printf("%d \n\n%d\n\n%d\n\n%d\n\n%d\n\n%d\n\n%d\n\n%d\n\n%d\n\n총 명령 %d 개 \n\n ", count[0], count[1], count[2], count[3], count[4], count[5], count[6], count[7], count[8], count_commend);
	//fprintf(COUNT, "512B :%d , 1024B : %d, 2048B : %d,32768B : %d, 8192B : %d, 16384B : %d, 12288B : %d, 32768B : %d, 32768B : %d ", count[0], count[1], count[2], count[3], count[4], count[5], count[6], count[7], count[8]);


	fclose(trace);
	fclose(COUNT);

}