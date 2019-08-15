#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

long long int LSN_minvalue;
long long int LSN_maxvalue;

char commend[8];
char sector_number[20];
char size[30];
char chip[8];
char time[20];

char time1[40];
char time2[40];

long long int CINT3,C_Check,LSN;

int SIZE;


char Reding[100];

void main(FILE* trace, FILE* User_file) {

	fopen_s(&trace, "2016021612-LUN6_4096.txt", "r");           

	if (trace == NULL) {                           
		puts("입력을 위한 파일을 열 수 없습니다.\n");         
		exit(1);                                   
	}
	

	fseek(trace, 0, SEEK_SET);

	while (!feof(trace)) {
		while (fgets(Reding, sizeof(Reding), trace)) {

			//printf("%s\n", Reding);
			strcpy(commend, strtok(Reding, ","));
			strcpy(size, strtok(NULL, ","));
			strcpy(sector_number, strtok(NULL, ","));
			strcpy(time, strtok(NULL, "\r\n"));


			LSN = atoll(sector_number);

			//printf("%d\n", LSN);
			//SIZE = atoi(size);
			//printf("%d\n", C_Check);

			//LSN = atoi(sector_number);


				//printf("%d\n", C_Check);
				if (LSN_maxvalue < LSN) {
					LSN_maxvalue = LSN;
				}
				if (LSN_minvalue > LSN) {
					LSN_minvalue = LSN;
				}

		}

	}

	printf("LSN 최대값 : %lld , LSN 최소값 : %lld", LSN_maxvalue, LSN_minvalue);


	fclose(trace);
	//fclose(User_file);

}