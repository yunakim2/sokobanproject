#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "linux_khbit.h"

int map1[254];
int map2[150];
int map3[180];
int map4[300];
int map5[234];

char username[10];

void mapOpen(char* fName);
void displayHelp();

void displayHelp() {
	char input;

	system("cls");
	printf("       hello ");
	for (int i = 0; i < 10; i++) {
		printf("%c", username[i]);
	}
	printf("\n\n");
	printf("h(왼쪽), j(아래), k(위), l(오른쪽) \n");
	printf("u(undo)\n");
	printf("r(replay)\n");
	printf("n(new)\n");
	printf("e(exit)\n");
	printf("s(save)\n");
	printf("f(file load)\n");
	printf("d(display help)\n");
	printf("t(top)\n\n");
	printf("아무키나 누르면 메인 메뉴로 이동합니다.\n");
	input = linux_kbhit();

}

void mapOpen(char* fName) {

	FILE* fp;
	fp = fopen(fName, "rt");

	int map1_$ = 0, map2_$ = 0, map3_$ = 0, map4_$ = 0, map5_$ = 0;
	int map1_O = 0, map2_O = 0, map3_O = 0, map4_O = 0, map5_O = 0;
	int i1 = 0;
	int i2 = 0;
	int i3 = 0;
	int i4 = 0;
	int i5 = 0;

	int a;

	if (fp == NULL) {
		printf("file open error ! \n");
		exit(0);
	}

	//레벨1 맵 생성
	while ((a = fgetc(fp)) != '2') {
		if (a == '1') {
			continue;
		}
		if (a == '$') {
			map1_$++;
		}
		else if (a == 'O') {
			map1_O++;
		}

		map1[i1] = a;
		i1++;
	}
	//printf("$ : %d\n", map1_$);
	//printf("O : %d\n", map1_O);

	//레벨2 맵 생성
	a = fgetc(fp);
	while ((a = fgetc(fp)) != '3') {
		if (a == '$') {
			map2_$++;
		}
		else if (a == 'O') {
			map2_O++;
		}
		map2[i2] = a;
		i2++;
	}
	//printf("$ : %d\n", map2_$);
	//printf("O : %d\n", map2_O);

	//레벨3 맵 생성
	a = fgetc(fp);
	while ((a = fgetc(fp)) != '4') {
		if (a == '$') {
			map3_$++;
		}
		else if (a == 'O') {
			map3_O++;
		}
		map3[i3] = a;
		i3++;
	}
	//printf("$ : %d\n", map3_$);
	//printf("O : %d\n", map3_O);

	//레벨4 맵 생성
	a = fgetc(fp);
	while ((a = fgetc(fp)) != '5') {
		if (a == '$') {
			map4_$++;
		}
		else if (a == 'O') {
			map4_O++;
		}
		map4[i4] = a;
		i4++;
	}
	//printf("$ : %d\n", map4_$);
	//printf("O : %d\n", map4_O);

	//레벨5 맵 생성
	a = fgetc(fp);
	while ((a = fgetc(fp)) != 'e') {
		if (a == '$') {
			map5_$++;
		}
		else if (a == 'O') {
			map5_O++;
		}
		map5[i5] = a;
		i5++;
	}

	//printf("$ : %d\n", map5_$);
	//printf("O : %d\n", map5_O);

	//예외처리 (각 레벨별로 $개수와 O개수가 다를때 오류 발생)
	if (map1_$ != map1_O || map2_$ != map2_O || map3_$ != map3_O || map3_$ != map3_O || map3_$ != map3_O) {
		printf("map이 올바르지않습니다.\n");
		printf("프로그램을 종료합니다...");
		exit(0);
	}

}
int main() {
	mapOpen("map.txt");
	char input;//키보드 입력값
	char username[10];//사용자이름
	for (int i = 0; i < 10; i++) {
		username[i] = 'n';
	}

	//불러온 MAP 출력해보기
	for (int q = 0; q < 254; q++) {

		printf("%c", map1[q]);
	}
	printf("\n");
	for (int q = 0; q < 150; q++) {
		printf("%c", map2[q]);
	}
	printf("\n");
	for (int q = 0; q < 180; q++) {
		printf("%c", map3[q]);
	}
	printf("\n");
	for (int q = 0; q < 300; q++) {
		printf("%c", map4[q]);
	}
	printf("\n");
	for (int q = 0; q < 234; q++) {
		printf("%c", map5[q]);
	}

	input = linux_kbhit();
	switch (input) {
	case 'd' :
		displayHelp();
		break;
	}
	printf("도움말 닫기\n");

	
	return 0;
}
