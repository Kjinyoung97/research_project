#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int LSN_minvalue;
int LSN_maxvalue;

char commend[8];
char sector_number[10];
char size[10];
//char chip_number[8];
char time[20];

int read_count, write_count;
int CINT3, C_Check, LSN;

int LSN_Count[1000000];
char Reding[50];

void main(FILE* trace, FILE* User_file) {

	fopen_s(&trace, "Chip_10_time_.txt", "r");

	if (trace == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	fopen_s(&User_file, "Chip10_LSN_Sequence.txt", "ab+");
	if (User_file == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	fseek(trace, 0, SEEK_SET);

	while (!feof(trace)) {
		for (int i = 0; i < 888264; i++) {
			while (fgets(Reding, sizeof(Reding), trace)) {
				//printf("%s\n", Reding);
				//strcpy(chip_number, strtok(Reding, ","));
				strcpy(sector_number, strtok(Reding, ","));
				//printf("%s\n", sector_number);
				strcpy(size, strtok(NULL, ","));
				//printf("%s\n", size);
				strcpy(commend, strtok(NULL, ","));
				//printf("%s\n", commend);
				strcpy(time, strtok(NULL, "/n"));
				//printf("%s\n", time);

				LSN = atoi(sector_number);

				LSN_Count[LSN] = LSN_Count[LSN] + 1;

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

			}
			fseek(trace, 0, SEEK_SET);
			fprintf(User_file,"LSN : %d, write_count : %d, read_count : %d",LSN,write_count,read_count);
			fputs("\r\n", User_file);
		}
	}


	printf("LSN 최대값 : %d, LSN 최소값 : %d", LSN_maxvalue, LSN_minvalue);


	fclose(trace);
	fclose(User_file);

}