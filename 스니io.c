#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

char commend[8];
char sector_number[10];
char size[10];
char size_sector[10];
char time1[30];
char time2[30];
char time3[30];
char time4[30];


int CINT3, C_Check, LSN;

char Reding1[200];


char change_commend[2];
int commend_count;

void main(FILE* trace, FILE* COUNT) {

	fopen_s(&trace, "log260_FaceBookHandOuts.txt", "r");

	if (trace == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}

	fopen_s(&COUNT, "넥서스31.txt", "ab+");
	if (COUNT == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}


	//fseek(trace, 0, SEEK_SET);


	while (!feof(trace)) {
		while (fgets(Reding1, sizeof(Reding1), trace)) {
			strcpy(sector_number, strtok(Reding1, "\t"));
			strcpy(size_sector, strtok(NULL, "\t"));
			strcpy(size, strtok(NULL, "\t"));
			strcpy(commend, strtok(NULL, "\t"));
			strcpy(time1, strtok(NULL, "\t"));
			strcpy(time2, strtok(NULL, "\t"));
			strcpy(time3, strtok(NULL, "\t")); 
			strcpy(time4, strtok(NULL, "\n"));

			LSN = atoi(sector_number);
			commend_count = atoi(commend);

			if (commend_count % 2 == 0) {
				change_commend[0] = 'r';
			}
			else {
				change_commend[0] = 'w';
			}

			//LSN_SAVE = LSN;

			fputs(change_commend, COUNT);
			fputs(",", COUNT);
			fputs(size, COUNT);
			fputs(",", COUNT);
			fputs(size_sector, COUNT);
			fputs(",", COUNT);
			fputs(time1, COUNT);
			fputs("\r\n", COUNT);



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