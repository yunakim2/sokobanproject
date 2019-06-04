

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<termio.h>

#define X 30 // ���ִ�X��
#define Y 30 // ���ִ�Y��
#define STAGE 5 //�ִ� �������� ��.

int getch(void); //getch�Լ�
void StartView(); // �ʱ� ����ȭ��
void Login(); // user �̸� ���� �˻� �� , username�� ����
void rankingview(int level); // ranking �����ֱ�
void rankingsave(); // ranking ���� ����
void rankingreset(); // ranking ���� ������ ����
void rankingcompare(int level); // ranking ���� ��
void rankinguproad(); // ranking ���� �ҷ�����
int StageClear();//�������� �Ϸ� Ȯ��
void ClearView();//�������� �Ϸ� ȭ��
void Replay();//�����
void Newplay();
void loadMap();//�� �ε�
void drawMap();//�� ���
void displayHelp();
void PlayerMoveAction();//�����̱�
void gotoxy(int, int);//���ϴ� ��ǥ�� ����Ҽ��ְ� �ϴ�  �Լ�
void SokobanfileSave(); // ���ڹ� ���� ���̺�
void SokobanfileUproad(); // ���ڹ� ���� ���ε�
void Option(char ch); // h,j,k,l ���� ������ Ű��
void MapClear(); // map �����
void Undo(); // ��ν���
void UndoMap(); //��θ�
void playerreset(); //�÷��̾� ��ġ

char stageData[6][30][30];//�� �Է¹ޱ�
char map[5][30][30];//���������� �� ����ϱ����� ���
char undo[5][30][30];//undo��
int levelX, levelY;//��ǥ
int u_levelX[5];//undo�ʿ��� �����X ��ǥ
int u_levelY[5];//undo�ʿ��� �����Y ��ǥ

char rankname[5][5][11]; //level�� ���� 5���� ranking data �̸�
int rankcount[5][5]; // level�� ���� 5���� ranking data count ����

char tempname[2][11]; // count �񱳸� ���� name �ӽ� �����
int tempcount[2]; // count �񱳸� ���� count �ӽ� �����
_Bool rank_bool=0; 
_Bool return_bool = 0;
int dx, dy; //�÷��̾� �̵�

char username[11]; // user �̸�
char inputname[11];  // input data
int usercount;
int userlevel = 0;

int undosaveCount; // ��� �� ���� Ƚ��
int undoCount; // ��� ���� Ƚ��


//����
int main()
{
	StartView();
	loadMap();

	int input;

	userlevel = 0; //����1�� �ش��ϴ� �� ���
	while (1)
	{
		memcpy(map, stageData[userlevel], sizeof(map));
		playerreset();

		MapClear();
		while (1)
		{
			drawMap();
			ClearView();
			if (return_bool) {
				return 0;
			}
		}
	}

	

	return 0;
}
void MapClear()
{
	system("clear");
	system("clear");
	
}
void playerreset() {
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			if (map[userlevel][y][x] == '@')
			{
				levelX = x;
				levelY = y + 1;
			}
		}
	}
	return;
}
//�ε�
void StartView()
{
	printf("sokoban\n");
	printf("start .... \n");

	Login();
	return;
}
//�α���
void Login()
{
	int length, input;
reinput: while (1)
{
	length = 0;
	printf("input name : ");
	scanf("%s", inputname);
	length = strlen(inputname);
	for (int i = 0; i < length; i++)
	{

		if (!((inputname[i] >= 65 && inputname[i] <= 90) || (inputname[i] >= 97 && inputname[i] <= 122)))
		{
			printf("�����ڸ� �����մϴ�. \n");
			goto reinput;
		}
	}

	if (length > 11)
	{
		printf("������ �ִ� 10���� ���� �����մϴ�.\n");
		printf("�ٽ� �Է����ּ��� ! \n");
	}

	else
	{
		for (int i = 0; i < length; i++)
		{
			username[i] = inputname[i];
		}
		break;
	}

}


		 printf("Hello %s", username);
		 input = getch();
		 MapClear();
		 return;
}
//��
void loadMap() {
	FILE* pFile = NULL;

	pFile = fopen("map.txt", "r");
	if (pFile != NULL)
	{
		char strTemp[30];


		int sa = 0;
		int i;
		int num_$[5] = { 0, 0, 0, 0, 0 };
		int num_O[5] = { 0, 0, 0, 0, 0 };

		i = 0;
		fgets(strTemp, sizeof(strTemp), pFile);
		while (strTemp[0] != 50)
		{
			fgets(strTemp, sizeof(strTemp), pFile);

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
			fgets(strTemp, sizeof(strTemp), pFile);

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
			fgets(strTemp, sizeof(strTemp), pFile);

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
			fgets(strTemp, sizeof(strTemp), pFile);

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
			fgets(strTemp, sizeof(strTemp), pFile);

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

		for (int a = 0; a < sizeof(num_$) / sizeof(int); a++) {
			//printf("num_$ : %d / num_O : %d\n", num_$[a], num_O[a]);

			if (num_$[a] != num_O[a]) {
				printf("map�� �ùٸ��� �ʽ��ϴ�.\n");
				printf("���α׷��� �����մϴ�...");
				return_bool = 1;
			}
		}


		fclose(pFile);
	}


	else
	{
		//���� ó��
	}

}

void drawMap()
{
	int mapX, mapY;
	for (mapY = 1; mapY < 31; mapY++)
	{
		for (mapX = 0; mapX < 30; mapX++)
		{
			if (map[userlevel][mapY - 1][mapX] == '\0') {
				break;
			}
			gotoxy(mapX, mapY);
			putchar(map[userlevel][mapY - 1][mapX]);

		}
	}
	gotoxy(levelX, levelY);
	putchar('@');
}

void PlayerMoveAction()
{
	int dx = 0, dy = 0;
	char ch;

	ch = getch();



	switch (ch)
	{
	case 'h':
	case 'H':
		//UndoMap();//undo�� ����
		usercount++;
		dx = -1; dy = 0; 
		return_bool = 0;
		break;
	case 'j':
	case 'J':
		//UndoMap();//undo�� ����
		usercount++;
		dx = 0; dy = 1; 
		return_bool = 0;
		break;
	case 'k':
	case 'K':
		//UndoMap();//undo�� ����
		usercount++;
		dx = 0; dy = -1; 
		return_bool = 0;
		break;
	case 'l':
	case 'L':
		//UndoMap();//undo�� ����
		usercount++;
		dx = 1; dy = 0; 
		return_bool = 0;
		break;
	}
	if (((((((ch != 'h' && ch != 'j') && ch != 'k') && ch != 'l') && ch != 'H') && ch != 'J') && ch != 'K') && ch != 'L')
	{
		Option(ch);
	}

	// �浹 üũ
	if (map[userlevel][levelY - 1 + dy][levelX + dx] == '#') // �տ� '#'���� ������
	{
		dx = 0; // �������� ����
		dy = 0;
	}
	if (map[userlevel][levelY - 1 + dy][levelX + dx] == '$') // '$'���ڸ� �����ٸ�
	{
		UndoMap();
		if (map[userlevel][levelY - 1 + 2 * dy][levelX + 2 * dx] == '.') // �� ���� �����̶��
		{
			map[userlevel][levelY - 1 + dy][levelX + dx] = '@'; // ������ �� �÷��̾� ��ǥ ����
			map[userlevel][levelY - 1 + 2 * dy][levelX + 2 * dx] = '$'; // ������ �� ���� ��ǥ ����
		}
		else if (map[userlevel][levelY - 1 + 2 * dy][levelX + 2 * dx] == '#' || map[userlevel][levelY - 1 + 2 * dy][levelX + 2 * dx] == '$') // �÷��̾ ���ڸ� �а� ������ ���� ���� # �̰ų� $ �̶��
		{
			dx = 0; // �������� ����
			dy = 0;
		}

	}
	if (map[userlevel][levelY - 1 + dy][levelX + dx] == '.') // �÷��̾ �����δٸ�
	{
		if (dx != 0 && dy == 0)
		{
			UndoMap();
		}
		else if (dy != 0 && dx == 0)
		{
			UndoMap();
		}//

	}
	if (map[userlevel][levelY - 1 + dy][levelX + dx] == 'O') // 'O'�� �����ٸ�
	{
		if (stageData[userlevel][levelY - 1][levelX] == 'O') // ���� �ʿ��� 'O'������
		{
			map[userlevel][levelY - 1 + dy][levelX + dx] = 'O'; // 'O' ��� ����
		}  //
		UndoMap();//
	}

	if (map[userlevel][levelY - 1 + 2 * dy][levelX + 2 * dx] == 'O' && map[userlevel][levelY - 1 + dy][levelX + dx] == '$') // ���ڸ� �а� �ְ�, ���� �տ� 'O'�� �ִٸ�
	{
		map[userlevel][levelY - 1 + 2 * dy][levelX + 2 * dx] = '$'; // ���ڸ� ������ ������

	}

	map[userlevel][levelY - 1][levelX] = '.'; // �÷��̾��� �� ��ġ�� ������

	if (stageData[userlevel][levelY - 1][levelX] == 'O') // ���� �ʿ��� 'O'������
	{
		map[userlevel][levelY - 1][levelX] = 'O'; // 'O' ��� ����
	}

	levelX += dx;
	levelY += dy;

}
void Option(char ch)
{
	int count;
	char ch2;
	if (((((((ch != 'h' && ch != 'j') && ch != 'k') && ch != 'l') && ch != 'H') && ch != 'J') && ch != 'K') && ch != 'L')
	{
		printf("%c", ch);
	}

	switch (ch)
	{
	case 's':
	case 'S':
		SokobanfileSave();
		break;


	case 'f':
	case 'F':
		SokobanfileUproad();
		break;


	case 'd':
	case 'D':
		displayHelp();
		break;

	case 'r':
	case 'R':
		Replay();
		break;


	case 'n':
	case 'N':
		Newplay();
		break;

	case 'u':
	case 'U':
		count = undosaveCount <= 6 ? undosaveCount : 6;
		if (undoCount < count) {
			Undo();
		}
		break;

	
	case 'e':
	case'E':
		MapClear();
		printf("SEE YOU %s ...\n", username);
		rankingsave();
		return_bool = 1;
		break;

	case 't':
	case 'T':
		ch2 = getch();
		switch (ch2)
		{
		case '1':
			rankingview(0);
			rank_bool = 0;
			break;
		case '2':  rankingview(1);
			rank_bool = 0;
			break;
		case '3':  rankingview(2);
			rank_bool = 0;
			break;
		case '4': rankingview(3);
			rank_bool = 0;
			break;
		case '5': rankingview(4);
			rank_bool = 0;
			break;
		default:
			rankingview(5);
			rank_bool = 0;
			break;
		}
	}

	return;

}

void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}


void displayHelp() {
	char input;

	MapClear();
	printf("       hello ");
	for (int i = 0; i < 11; i++) {
		printf("%c", username[i]);
	}
	printf("\n\n");
	printf("h(����), j(�Ʒ�), k(��), l(������) \n");
	printf("u(undo)\n");
	printf("r(replay)\n");
	printf("n(new)\n");
	printf("e(exit)\n");
	printf("s(save)\n");
	printf("f(file load)\n");
	printf("d(display help)\n");
	printf("t(top)\n\n");
	printf("�ƹ�Ű�� ������ ���� �޴��� �̵��մϴ�.\n");
	input = getch();

}

//�������� �Ϸ�Ǿ����� Ȯ��
int StageClear() {
	int x, y;
	for (x = 0; x < 30; x++) {
		for (y = 0; y < 30; y++) {
			if (map[userlevel][y][x] == 'O') {
				return 0;
			}
		}
	}
	return 1;
}
//�������� �Ϸ�ȭ��
void ClearView() {
	
	PlayerMoveAction();

	if (StageClear()) { // Ŭ���� Ȯ��

		if (userlevel < 4) { // ���� �������� ���
			MapClear();
			printf("%d Stage Clear!\n", userlevel + 1);
			printf("Let's go Next Stage!\n");


			rankingsave();
			userlevel++;
			usercount = 0;
			printf("Please press any key");
			char ch;
			ch = getch();
			if (ch != 0) {
				playerreset();
				return_bool = 0;
			}

		}
		else if (userlevel == 4) {
			MapClear();
			printf("�ڡڡڡڡڡ�You clear all stages!�ڡڡڡڡڡ�\n");
			printf("�ڡڡڡڡڡڡڡڡڡڡ�Conglatulate�ڡڡڡڡڡڡڡڡڡڡ�\n");
			rankingsave();
			return_bool = 1;
			return;
		}
		MapClear();
	}
}

//�����
void Replay() {
	memcpy(map, stageData[userlevel], sizeof(map));
	while (1)
	{
		for (int y = 0; y < 30; y++)
		{
			for (int x = 0; x < 30; x++)
			{
				if (map[userlevel][y - 1][x] == '@')
				{
					levelX = x;
					levelY = y;
				}
			}
		}

		MapClear();
		while (1)
		{
			//         MapClear();
			drawMap();
			PlayerMoveAction();
		
		}
	}
	return;
}

void Newplay() {
	memcpy(map, stageData[userlevel], sizeof(map));
	MapClear();

	usercount = 0;
	undoCount = 5; // ��� ���� Ƚ��
	userlevel = 0; //����1�� �ش��ϴ� �� ���
	while (1)
	{
		for (int y = 0; y < 30; y++)
		{
			for (int x = 0; x < 30; x++)
			{
				if (map[userlevel][y - 1][x] == '@')
				{
					levelX = x;
					levelY = y;
				}
			}
		}

		MapClear();
		while (1)
		{
			//         MapClear();
			drawMap();
			PlayerMoveAction();
		
		}
	}


	return;
}
// ���ڹ� ���� ����
void SokobanfileSave()
{
	FILE* sokobansave;
	_Bool flag;
	char input;
	MapClear();
	levelX;
	levelY;

	map[userlevel][levelY - 1][levelX] = '@';

	printf("���ڹ� ���� ����\n");
	input = getch();


	sokobansave = fopen("sokoban.txt", "w");
	if (sokobansave == NULL)
	{
		printf("sokoban.txt File open Error!!\n");
		return;
	}
	fprintf(sokobansave, "%s\n", username);
	fprintf(sokobansave, "%d\n", userlevel + 1);
	fprintf(sokobansave, "%d\n", usercount);
	for (int i = userlevel; i < 5; i++) {
		flag = 0;
		fprintf(sokobansave, "%d\n", i + 1);
		for (int j = 0; j < 30; j++) {
			for (int k = 0; k < 30; k++) {
				fprintf(sokobansave, "%c", map[i][j][k]);
				//printf("%c", map[i][j][k]);
				if (map[i][j][k] == '\n' || map[i][j][k] == '\0') {
					break;
				}
				/*if (map[i][j][k] == '\0') {
				if (i == 4) {
				flag = 1;
				printf("e");

				}
				break;
				}*/

			}
			if (map[i][j + 1][0] == '\0') {
				if (i == 4) {
					fprintf(sokobansave, "e");
				}
				break;
			}

		}
	}

	fclose(sokobansave);

	return;
}
void SokobanfileUproad() // ���ڹ� ���� ���ε�
{
	FILE* sokobanopen;
	char name[11];
	int count, level;
	char input;
	int i;

	MapClear();


	sokobanopen = fopen("sokoban.txt", "r");

	if (sokobanopen != NULL)
	{
		fscanf(sokobanopen, "%s", name);
		for (i = 0; i < 11; i++)
		{
			username[i] = name[i];
		}

		fscanf(sokobanopen, "%d", &level);
		userlevel = --level;
		fscanf(sokobanopen, "%d", &count);
		usercount = count;


		//printf("username : %s \n userlevel: %d \n usercount : %d\n", username, userlevel, usercount);

		//input = _getch();
		char strTemp[30];
		int sa = 0;
		int i = 0, k;
		int num_$[5] = { 0, 0, 0, 0, 0 };
		int num_O[5] = { 0, 0, 0, 0, 0 };

		fgets(strTemp, sizeof(strTemp), sokobanopen);
		fgets(strTemp, sizeof(strTemp), sokobanopen);

		for (k = userlevel; k < 5; k++)
		{
			while ((strTemp[sa] != (k + 50)))
			{
				fgets(strTemp, sizeof(strTemp), sokobanopen);

				if (strTemp[0] == 'e')
				{
					break;
				}
				for (sa = 0; strTemp[sa];) {
					if (strTemp[0] == k + 50) {
						break;
					}
					else if (strTemp[sa] == '$') {
						num_$[0]++;
					}
					else if (strTemp[sa] == 'O') {
						num_O[0]++;
					}
					printf("%c", strTemp[sa]);
					stageData[k][i][sa] = strTemp[sa];
					sa++;
				}
				i++;
			}
			i = 0;

		}
		//while (1)
		//{
		memcpy(map, stageData[userlevel], sizeof(map));
		for (int y = 0; y < 30; y++)
		{
			for (int x = 0; x < 30; x++)
			{
				if (map[userlevel][y][x] == '@')
				{
					levelX = x;
					levelY = y + 1;
					//map[userlevel][y][x] = ' ';
				}
			}
		}
		//}

		MapClear();


	}
	else
	{
		printf("����� sokoban.txt ������ �����ϴ�.");
	}

	printf("���� ���ε�\n");
	input = getch();
	MapClear();
	drawMap();
	return;

}
int getch(void)
{
int ch;
struct termios buf;
struct termios save;

tcgetattr(0, &save);

buf = save;

buf.c_lflag &= ~(ICANON | ECHO);
buf.c_cc[VMIN] = 1;
buf.c_cc[VTIME] = 0;

tcsetattr(0, TCSAFLUSH, &buf);

ch = getchar();
tcsetattr(0, TCSAFLUSH, &save);

return ch;
}



// ��� �� ����
void UndoMap()
{
	for (int i = 4; i > 0; i--) {
		for (int j = 0; j < 30; j++) {
			for (int k = 0; k < 30; k++) {
				undo[i][j][k] = undo[i - 1][j][k];
			}
		}
		undo[i];
		u_levelX[i] = u_levelX[i - 1];
		u_levelY[i] = u_levelY[i - 1];
	}
	MapClear();


	for (int j = 0; j < 30; j++) {
		for (int k = 0; k < 30; k++) {
			undo[0][j][k] = map[userlevel][j][k];

		}
	}
	u_levelX[0] = levelX;
	u_levelY[0] = levelY;
	undosaveCount++;
}
// ��� ����
void Undo()
{
	for (int j = 0; j < 30; j++) {
		for (int k = 0; k < 30; k++) {
			map[userlevel][j][k] = undo[0][j][k];
		}
	}

	levelX = u_levelX[0];
	levelY = u_levelY[0];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 30; j++) {
			for (int k = 0; k < 30; k++) {
				undo[i][j][k] = undo[i + 1][j][k];
			}
			undo[i][j];
		}

		u_levelX[i] = u_levelX[i + 1];
		u_levelY[i] = u_levelY[i + 1];
	}
	undoCount++;
}
//��ŷ
void rankingcompare(int level)
{
	//printf("username : %s \n", username);
	int i, j, k;
	rankinguproad();
	if (level <= userlevel)
	{
		for (i = 0; i < 4; i++)
		{
			if (rankcount[level][i] > usercount || rankcount[level][i] == 0)
			{
				for (j = 0; j < 4 - i; j++)
				{
					rankcount[level][4 - j] = rankcount[level][3 - j];
					for (k = 0; k < 11; k++)
					{

						rankname[level][4 - j][k] = rankname[level][3 - j][k];


					}

				}
				for (k = 0; k < 11; k++) {
					rankname[level][i][k] = username[k];
				}
				rankcount[level][i] = usercount;
				break;
			}
		}
		if (rankcount[level][i] > usercount || rankcount[level][i] == 0)
		{
			rankcount[level][i] = usercount;


			for (k = 0; k < 11; k++)
			{
				rankname[level][i][k] = username[k];
			}
		}
		/*for (int i = 0; i < 5; i++)
		{
		printf("ranking compare %s  %d\n", rankname[level][i], rankcount[level][i]);
		}
		*/
	}



}


void rankingview(int level)
{
	//printf("rankingview username , usercount %s %d \n", username, usercount);
	int s;
	int ch;
	int i, j, k;
	MapClear();
	rank_bool = 1;
	if (rank_bool)
	{
		while (1)
		{

			if (level < 5)
			{

				printf("map %d\n", level + 1);

				rankingcompare(level);
				for (j = 0; j < 3; j++)
				{
					//printf("view ranking name : %c %c %c %c %c \n", rankname[level][j][0] , rankname[level][j][1], rankname[level][j][2], rankname[level][j][3], rankname[level][j][4]);
					//printf("ranking count : %d \n", rankcount[level][j]);
					for (k = 0; k < 11; k++)
					{


						if (rankname[level][j][0] == ' ' && rankname[level][j][1] == ' ' && rankname[level][j][2] == '\0')
						{
							s = 0;
							break;
						}
						/*(else if (rankname[level][j][0] == ' ' && rankname[level][j][1] == '\0')
						{
						s = 0;
						break;
						}
						*/
						else
						{
							s = 1;
							break;
						}

					}
					if (s == 1)
					{
						printf("%s  ", rankname[level][j]);
						printf("%d", rankcount[level][j]);
					}
					printf("\n");

				}
			}
			if (level == 5)
			{
				for (i = 0; i < 5; i++)
				{
					printf("map %d\n", i + 1);
					rankingcompare(i);
					for (j = 0; j < 3; j++)
					{
						for (k = 0; k < 11; k++)
						{
							if (rankname[i][j][0] == ' ' && rankname[i][j][1] == ' ' && rankname[i][j][2] == '\0')
							{
								s = 0;
								break;
							}
							/*else if (rankname[level][j][0] == ' ' && rankname[level][j][1] == '\0')
							{
							s = 0;
							break;
							}
							*/
							else
							{
								s = 1;
								break;
							}

						}
						if (s == 1)
						{
							printf("%s  ", rankname[i][j]);
							printf("%d", rankcount[i][j]);
						}
						printf("\n");

					}
				}
			}
			printf("�������� �ƹ�Ű�� �����ÿ�.\n");

			ch = getch();

			if (ch)
			{
				break;
			}
		}
	}
	



	return;
}

void rankingreset()
{



	int i, j; //k;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			rankcount[i][j] = 0;
			rankname[i][j][0] = ' ';
			rankname[i][j][1] = ' ';
			rankname[i][j][2] = '\0';


		}
	}

	return;
}
void rankingsave()
{


	FILE* ranksave;
	int i, j, k;

	if(!rank_bool)
	for (i = 0; i <= userlevel; i++)
	{
		rankingcompare(i);
	}
	ranksave = fopen("ranking.txt", "w");
	
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 5; j++)

			{
				//printf("rankingname : %s , rankcount : %d\n", rankname[i][j], rankcount[i][j]);
				if (rankname[i][j][0] == ' ' && rankname[i][j][1] == ' ' && rankname[i][j][2] == '\0')
				{
					fprintf(ranksave, "---");
					//printf("--- ����\n");
				}
				else
				{
					fprintf(ranksave, "%s", rankname[i][j]);
					//printf("%s \n", rankname[i][j]);
				}
				fprintf(ranksave, " %d \n", rankcount[i][j]);

			}
		}
	


	fclose(ranksave);


}
void rankinguproad()
{


	FILE* rankopen;
	int i, j, k;
	char name[11];
	int count;
	//char a;
	int ret;
	rankopen = fopen("ranking.txt", "r");

	if (rankopen == NULL)
	{
		rankingreset();
		rankingsave();


	}


	rankopen = fopen("ranking.txt", "r");


	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			ret = fscanf(rankopen, "%s %d", name, &count);
			//printf("map %d rankuproad : %s %d\n", i + 1, name, count);


			for (k = 0; k < 11; k++)
			{

				if (name[0] == '-' && name[1] == '-' && name[2] == '-' && name[3] == '\0')
				{
					rankname[i][j][0] = ' ';
					rankname[i][j][1] = ' ';
					rankname[i][j][2] = '\0';
					break;
				}
				if (name[k] == '\0')
				{
					break;
				}
				rankname[i][j][k] = name[k];

			}
			rankcount[i][j] = count;
		}
	}

	fclose(rankopen);
	return;
}
