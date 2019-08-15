#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int LSN_minvalue;
int LSN_maxvalue;
int i = 0;
char commend[8];
char sector_count[5];
char sector_number[10];
char size[10];
//char chip_number[8];
char time[20];

long long int LSN_SAVE;

//long long int read_count[900000];
//long long int write_count[900000];
long long int CINT3, C_Check, LSN;
int I_size, sector_coun;

//int LSN_Count[5429];
char Reding[50];
char count_read_LSN[20];
char count_LSN[15];
char count_count[5];

void main(FILE* trace, FILE* COUNT) {

	fopen_s(&trace, "2016021613-LUN6_1024순서정렬.csv", "r");

	if (trace == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	fopen_s(&COUNT, "2016021613-LUN6_1024순서정렬_WR_sector.txt", "ab+");
	if (COUNT == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}


	//fseek(trace, 0, SEEK_SET);


	while (!feof(trace)) {
		while (fgets(Reding, sizeof(Reding), trace)) {
			strcpy(commend, strtok(Reding, ","));
			strcpy(size, strtok(NULL, ","));
			strcpy(sector_number, strtok(NULL, ","));
			//strcpy(time, strtok(NULL, "/n"));

			LSN = atoll(sector_number);
			//I_size = atoi(size);
			//sector_coun = I_size / 512;
			//itoa(sector_coun, sector_count, 10);
		
			//LSN_SAVE = LSN;

			//fputs(commend, COUNT);
			//fputs(sector_count, COUNT);
			//fputs("#", COUNT);

			if (LSN != LSN_SAVE) {
				fputs("\r\n", COUNT);
			}

			fputs(commend, COUNT);

			LSN_SAVE = LSN;

					/*fputs("\t", User_file);
					fputs(size, User_file);
					fputs("\t", User_file);
					fputs(commend, User_file);
					fputs("\t", User_file);
					fputs(time, User_file);


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