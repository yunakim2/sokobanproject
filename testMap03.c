#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include <unistd.h>

void loadMap();
void drawMap(int);
void gotoxy(int ,int);
char stageData[6][30][30];
char map[30][30];

int levelNum;//현재 레벨 정보
int levelX, levelY;

int main()
{	
	loadMap();
	
	levelNum = 1;
	while (1)
	{
		memcpy(map, stageData[levelNum], sizeof(map));
		system("clear");
		while (1)
		{
			drawMap(levelNum);
			
		}
		sleep(10);
		
	}
	getchar();

	return 0;
}

void loadMap() {
	FILE *pFile = NULL;

	pFile = fopen("map.txt", "r");
	if (pFile != NULL)
	{
		char strTemp[30];
		char *pStr;

		int sa = 0;
		int i;
		int num_$[5] = { 0, 0, 0, 0, 0 };
		int num_O[5] = { 0, 0, 0, 0, 0 };

		i = 0;
		pStr = fgets(strTemp, sizeof(strTemp), pFile);
		while (strTemp[0] != 50)
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 50) {
					break;
				}
				else if (strTemp[sa] == '$') {
					num_$[0]++;
				}
				else if (strTemp[sa] == 'O') {
					num_O[0]++;
				}

				stageData[0][i][sa] = strTemp[sa];
				
				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 51)
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 51) {
					break;
				}
				else if (strTemp[sa] == '$') {
					num_$[1]++;
				}
				else if (strTemp[sa] == 'O') {
					num_O[1]++;
				}
				stageData[1][i][sa] = strTemp[sa];

				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 52)
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 52) {
					break;
				}
				else if (strTemp[sa] == '$') {
					num_$[2]++;
				}
				else if (strTemp[sa] == 'O') {
					num_O[2]++;
				}
				stageData[2][i][sa] = strTemp[sa];

				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 53)
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 53) {
					break;
				}
				else if (strTemp[sa] == '$') {
					num_$[3]++;
				}
				else if (strTemp[sa] == 'O') {
					num_O[3]++;
				}
				stageData[3][i][sa] = strTemp[sa];

				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 101)
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 101) {
					break;
				}
				else if (strTemp[sa] == '$') {
					num_$[4]++;
				}
				else if (strTemp[sa] == 'O') {
					num_O[4]++;
				}
				stageData[4][i][sa] = strTemp[sa];

				sa++;
			}
			i++;
		}

		for (int a = 0; a < sizeof(num_$)/sizeof(int); a++) {
			printf("num_$ : %d / num_O : %d\n", num_$[a], num_O[a]);

			if (num_$[a] != num_O[a]) {
				printf("map이 올바르지 않습니다.\n");
				printf("프로그램을 종료합니다...");
				exit(0);
			}
		}

		
		fclose(pFile);
	}


	else
	{
		//에러 처리
	}

}

void drawMap(int levelNum)
{
	int mapX, mapY;
	for (mapY = 0; mapY < 30; mapY++)
	{
		for (mapX = 0; mapX < 30; mapX++)
		{
			//putchxy(mapX, mapY, map[mapY][mapX]);
			gotoxy(mapX, mapY);
			//move_cur(mapX, mapY);
			
			putchar(map[mapY][mapX]);
			if (map[mapY][mapX] == '\0') {
				break;
			}
		}
		/*if (map[mapY][mapX + 1] == '\0') {
			break;
		}*/
	}
	//sleep(5);
}

void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}
