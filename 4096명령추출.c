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

char time1[40];
char time2[40];
char time3[30];
char time4[30];


int CINT3, C_Check, LSN;

char Reding1[200];


char change_commend[2];
int commend_count;

void main(FILE* trace, FILE* COUNT) {

	fopen_s(&trace, "2016021613-LUN6.csv", "r");

	if (trace == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	fopen_s(&COUNT, "2016021613-LUN6_1024.txt", "ab+");
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
			
			if (SIZE == 1024) {

				fputs(commend, COUNT);
				fputs(",", COUNT);
				fputs(size, COUNT);
				fputs(",", COUNT);
				fputs(sector_number, COUNT);
				fputs(",", COUNT);
				fputs(time1, COUNT);
				fputs("\r\n", COUNT);

			
			}

			/* fputs(change_commend, COUNT);
			fputs(",", COUNT);
			fputs(size, COUNT);
			fputs(",", COUNT);
			fputs(size_sector, COUNT);
			fputs(",", COUNT);
			fputs(time1, COUNT);
			fputs("\r\n", COUNT);*/



			//printf("%d\n", LSN);
			//C_Check = atoi(chip_number);
			//printf("%d\n", C_Check);

			//LSN = atoi(sector_number);

			//if (C_Check == 10) {
				//printf("%d\n", C_Check);
				/*if (LSN == i) {

					if ((strcmp(commend, "r") == 0)) {
						read_count++;
					}
					else  {
						write_count++;
					}
					fputs(sector_number, User_file);
					fputs("\t", User_file);
					fputs(size, User_file);
					fputs("\t", User_file);
					fputs(commend, User_file);
					fputs("\t", User_file);
					fputs(time, User_file);
					fputs("\r\n", User_file);
				}*/


				//sector_number[0] = '\0';
		//fprintf(User_file, "LSN : %d, write_count : %d, read_count : %d", LSN, write_count, read_count);
		//fputs("\r\n", User_file);
		}
	}

	//printf("LSN 최대값 : %d, LSN 최소값 : %d", LSN_maxvalue, LSN_minvalue);


	fclose(trace);
	fclose(COUNT);

}