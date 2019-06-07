


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<termio.h>

#define X 30 // 맵최대X값
#define Y 30 // 맵최대Y값
#define STAGE 5 //최대 스테이지 값.


#define X 30 // 맵최대X값
#define Y 30 // 맵최대Y값
#define STAGE 5 //최대 스테이지 값.

int getch(void); //getch함수
void StartView(); // 초기 시작화면
void Login(); // user 이름 조건 검사 후 , username에 저장
void rankingview(int level); // ranking 보여주기
void rankingsave(); // ranking 파일 저장
void rankingreset(); // ranking 파일 없을시 리셋
void rankingcompare(int level); // ranking 파일 비교
void rankinguproad(); // ranking 파일 불러오기
int StageClear();//스테이지 완료 확인
void ClearView();//스테이지 완료 화면
void Replay();//재시작
void Newplay(); // 새로시작
void loadMap();//맵 로드
void drawMap();//맵 출력
void displayHelp(); // 도움말 출력
void PlayerMoveAction();//움직이기
void gotoxy(int, int);//원하는 좌표에 출력할수있게 하는  함수
void SokobanfileSave(); // 소코반 파일 세이브
void SokobanfileUproad(); // 소코반 파일 업로드
void Option(char ch); // h,j,k,l 제외 나머지 키값
void MapClear(); // map 지우기
void Undo(); // 언두실행
void UndoMap(); //언두맵
void playerreset(); //플레이어 위치

char stageData[6][30][30];//맵 입력받기
char map[5][30][30];//스테이지별 맵 출력하기위해 사용
char undo[5][30][30];//undo맵
int levelX, levelY;//좌표
int u_levelX[5];//undo맵에서 사용자X 좌표
int u_levelY[5];//undo맵에서 사용자Y 좌표

char rankname[5][5][11]; //level별 상위 5명의 ranking data 이름
int rankcount[5][5]; // level별 상위 5명의 ranking data count 갯수

char tempname[2][11]; // count 비교를 위한 name 임시 저장소
int tempcount[2]; // count 비교를 위한 count 임시 저장소
_Bool rank_bool = 0;
_Bool return_bool = 0;
int dx, dy; //플레이어 이동

char username[11]; // user 이름
char inputname[11];  // input data
int usercount = 0; // user 움직인 횟수 count
int userlevel = 0; // user 레벨

int undoCount = 0; // 언두 가능 횟수

char ch, ch2; //ch - 키 입력 ch2- ranking 키 입력
int mX, mY; // 맵 끝부분 위치

//메인
int main()
{
	StartView(); // 시작화면 출력
	loadMap(); // 맵 불러오기


	userlevel = 0; //레벨에 해당하는 맵 출력
	while (1)
	{
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					map[k][j][i] = stageData[k][j][i];
				}
			}
		}
		playerreset(); // 플레이어 @ 위치 찾기

		MapClear();
		while (1)
		{
			drawMap();//맵 그리기
			ClearView(); // 움직임 동작, 게임키, 스테이지완료화면
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

}

void playerreset() { // 플레이어 위치 찾기
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			if (map[userlevel][y][x] == '@')
			{
				levelX = x + 1;
				levelY = y + 1;
			}
		}
	}
	return;
}

//로딩
void StartView()
{
	printf("sokoban\n");
	printf("start .... \n");

	Login();
	return;
}

//로그인
void Login()
{
	int length;
reinput: while (1)
{
	length = 0;
	printf("input name : ");
	scanf("%s", inputname);
	length = strlen(inputname);
	for (int i = 0; i < length; i++)
	{
		//inputname이 영문자로만 구성되었는지 검사
		if (!((inputname[i] >= 65 && inputname[i] <= 90) || (inputname[i] >= 97 && inputname[i] <= 122)))
		{
			printf("영문자만 가능합니다. \n");
			printf("다시 입력해주세요 ! \n");
			goto reinput;
		}
	}
	// inputname이 10개의 문자 이내로 구성되었는지 검사
	if (length > 11)
	{
		printf("영문자 최대 10문자 까지 가능합니다.\n");
		printf("다시 입력해주세요 ! \n");
	}
	//inputname이 영문자 10문자 이내로 구성되면 username 에 저장
	else
	{
		for (int i = 0; i < length; i++)
		{
			username[i] = inputname[i];
		}
		break;
	}

}



		 MapClear();
		 return;
}

//맵 불러오기
void loadMap() {
	FILE* pFile = NULL;

	pFile = fopen("map.txt", "r"); //map.txt불러오
	if (pFile != NULL)
	{
		char strTemp[30];


		int sa = 0;
		int i;
		int num_$[5] = { 0, 0, 0, 0, 0 };
		int num_O[5] = { 0, 0, 0, 0, 0 };

		i = 0;
		fgets(strTemp, sizeof(strTemp), pFile);
		while (strTemp[0] != 50)// 2가 나오기 전까지 strTemp에 읽어오기
		{
			fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 50) {
					break;
				}
				else if (strTemp[sa] == '$') { //레벨1 맵의 '$' 개수
					num_$[0]++;
				}
				else if (strTemp[sa] == 'O') { //레벨1 맵의 'O' 개수
					num_O[0]++;
				}


				stageData[0][i][sa] = strTemp[sa]; // 레벨1에 해당하는 맵 stageData[0]에 저장

				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 51) //3이 나오기 전까지 strTemp에 읽어오기
		{
			fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 51) {
					break;
				}
				else if (strTemp[sa] == '$') { //레벨2 맵의 '$' 개수
					num_$[1]++;
				}
				else if (strTemp[sa] == 'O') { //레벨2 맵의 'O' 개수
					num_O[1]++;
				}
				stageData[1][i][sa] = strTemp[sa]; // 레벨2에 해당하는 맵을 stageData[1]에 저장

				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 52) // 4가 나오기 전까지 strTemp에 읽어오기
		{
			fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 52) {
					break;
				}
				else if (strTemp[sa] == '$') { //레벨3 맵의 '$' 개수
					num_$[2]++;
				}
				else if (strTemp[sa] == 'O') { //레벨3 맵의 'O' 개수
					num_O[2]++;
				}
				stageData[2][i][sa] = strTemp[sa];// 레벨3에 해당하는 맵을 stageData[2]에 저장

				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 53)// 5가 나오기전까지 strTemp에 읽어오기
		{
			fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 53) {
					break;
				}
				else if (strTemp[sa] == '$') { // 레벨4 맵의 '$' 개수
					num_$[3]++;
				}
				else if (strTemp[sa] == 'O') { //레벨 4 맵의 'O'개수
					num_O[3]++;
				}
				stageData[3][i][sa] = strTemp[sa];// 레벨4에 해당하는 맵을 stageData[3]에 저장
				sa++;
			}
			i++;
		}

		i = 0;
		while (strTemp[0] != 101) // e가 나오기전까지 strTemp에 읽어오기
		{
			fgets(strTemp, sizeof(strTemp), pFile);

			for (sa = 0; strTemp[sa];) {
				if (strTemp[0] == 101) {
					break;
				}
				else if (strTemp[sa] == '$') { //레벨5 맵의 '$' 개수
					num_$[4]++;
				}
				else if (strTemp[sa] == 'O') { //레벨 5맵의 'O' 개수
					num_O[4]++;
				}
				stageData[4][i][sa] = strTemp[sa]; //레벨5에 해당하는 맵을 stageData[4]에 저장

				sa++;
			}
			i++;
		}

		for (int a = 0; a < sizeof(num_$) / sizeof(int); a++) {

			if (num_$[a] != num_O[a]) { //각 맵 별로 '$' 개수와 'O' 개수가 일치하는지 비교
				printf("map이 올바르지 않습니다.\n");
				printf("프로그램을 종료합니다...");
				return_bool = 1;
			}
		}


		fclose(pFile);
	}


	else
	{
		//에러 처리
	}

}

void drawMap()
{

	int mapX, mapY;

	for (mapY = 1; mapY < 31; mapY++) //맵이 출력될 y좌표
	{
		for (mapX = 1; mapX < 31; mapX++) //맵이 출력될 x좌표
		{
			if (map[userlevel][mapY - 1][mapX - 1] == '\n' || map[userlevel][mapY - 1][mapX - 1] == '\0') {
				break;
			}
			gotoxy(mapX, mapY + 2);//mapX, mapY + 2로 커서 이동
			putchar(map[userlevel][mapY - 1][mapX - 1]);//이동한 위치에 맵내용 하나씩 출력

		}
		if (map[userlevel][mapY - 1][0] == '\0') {
			break;
		}
	}
	mX = mapX;
	mY = mapY;
	gotoxy(levelX, levelY + 2); // '@'위치로 이동
	putchar('@'); // '@' 출력
	gotoxy(mX, mY + 3);
	printf("(Command)");
}

void PlayerMoveAction()
{
	gotoxy(1, 1); //x좌표 1, y좌표 1로 이동
	printf("Hello %s", username);//hello username 출력

	int dx = 0, dy = 0;//플레이어 위치 증감
	char ch1;

	ch1 = getch();
	ch = ch1;

	switch (ch1)
	{
	case 'h':
	case 'H':
		usercount++;
		dx = -1; dy = 0;//좌로 이동
		return_bool = 0;
		break;
	case 'j':
	case 'J':
		usercount++;
		dx = 0; dy = 1;//하로 이동
		return_bool = 0;
		break;
	case 'k':
	case 'K':
		usercount++;
		dx = 0; dy = -1;//상으로 이동
		return_bool = 0;
		break;
	case 'l':
	case 'L':
		usercount++;
		dx = 1; dy = 0;//우로 이동
		return_bool = 0;
		break;
	}
	if (((((((ch1 != 'h' && ch1 != 'j') && ch1 != 'k') && ch1 != 'l') && ch1 != 'H') && ch1 != 'J') && ch1 != 'K') && ch1 != 'L')
	{
		Option(ch1);
	}

	// 충돌 체크
	if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == '#') // 앞에 '#'벽이 있으면
	{
		dx = 0; // 움직이지 않음
		dy = 0;
	}
	if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == '$') // '$'상자를 만난다면
	{
		if (map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == '.') // 그 앞이 공백이라면
		{
			UndoMap();
			map[userlevel][levelY - 1 + dy][levelX - 1 + dx] = '@'; // 움직인 후 플>레이어 좌표 저장
			map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] = '$'; // 움직>인 후 상자 좌표 저장
		}
		else if (map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == 'O') // 그 >앞이 창고라면
		{
			UndoMap();
			map[userlevel][levelY - 1 + dy][levelX - 1 + dx] = '@'; // 움직인 후 플>레이어 좌표 저장
			map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] = '$'; // 움직>인 후 상자 좌표 저장
		}

		else if (map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == '#' || map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == '$') // 플레이어가 상자를 밀고 있을때 상자 앞이 # 이거나 $ 이라면
		{
			dx = 0; // 움직이지 않음
			dy = 0;
		}

	}
	if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == '.')
	{
		if (dx != 0 && dy == 0)
		{
			UndoMap();
		}
		else if (dy != 0 && dx == 0)
		{
			UndoMap();
		}
		//플레이어가 움직일때만 움직이기 전 상태 저장
	}
	if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == 'O') // 'O'를 만난다면
	{
		if (dx != 0 && dy == 0)
		{
			UndoMap();
		}
		else if (dy != 0 && dx == 0)
		{
			UndoMap();
		}
		//플레이어가 움직인다면 움직이기 전 상태 저장
		if (stageData[userlevel][levelY - 1][levelX - 1] == 'O') // 원래 맵에서 'O'였으면
		{
			map[userlevel][levelY - 1 + dy][levelX - 1 + dx] = 'O'; // 'O' 계속 유지
		}
	}


	if (map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == 'O' && map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == '$') // 상자를 밀고 있고, 상자 앞에 'O'가 있다면
	{
		map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] = '$'; // 상자를 앞으로 움직임

	}

	map[userlevel][levelY - 1][levelX - 1] = '.'; // 플레이어의 전 위치를 지워줌

	if (stageData[userlevel][levelY - 1][levelX - 1] == 'O') // 원래 맵에서 'O'였으면
	{
		map[userlevel][levelY - 1][levelX - 1] = 'O'; // 'O' 계속 유지
	}

	levelX += dx;
	levelY += dy;

}
void Option(char ch1)
{
	char ch3;


	switch (ch1)
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
		MapClear();
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
		if (undoCount < 5) {
			Undo();
		}
		break;


	case 'e':
	case'E':
		MapClear();
		rankingsave();
		printf("SEE YOU %s ...\n", username);
		return_bool = 1;
		break;

	case 't':
	case 'T':
		ch3 = getch();
		ch2 = ch3;
		switch (ch3)
		{
		case '1':
			rankingview(0);
			rank_bool = 0;
			MapClear();
			break;
		case '2':  rankingview(1);
			rank_bool = 0;
			MapClear();
			break;
		case '3':  rankingview(2);
			rank_bool = 0;
			MapClear();
			break;
		case '4': rankingview(3);
			rank_bool = 0;
			MapClear();
			break;
		case '5': rankingview(4);
			rank_bool = 0;
			MapClear();
			break;
		case '\n':
			rankingview(5);
			rank_bool = 0;
			MapClear();
			break;
		}
	default: // h j k l e E d D r R n N t 이외의 문자를 입력받으면 ClearView 다시 호출
		MapClear();
		drawMap();
		ClearView();
		break;
	}


}

void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}


void displayHelp() { //도움말 출력
	char input = '?';
	while (input != '\n') { //enter가 입력될때까지 반복

		MapClear();
		printf("Hello %s", username);

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
		printf("엔터키를 누르면 메인 메뉴로 이동합니다.\n");

		gotoxy(mX, mY + 3);
		printf("(Command)");
		printf("%3c", ch);
		input = getch();
		return_bool = 0;
		MapClear();
	}
}

//스테이지 완료되었는지 확인
int StageClear() {
	int x, y;
	for (x = 0; x < 30; x++) {
		for (y = 0; y < 30; y++) {
			if (map[userlevel][y][x] == 'O') { // 만약 맵에 구멍(O)이 있으면 0을 리턴
				return 0;
			}
		}
	}
	return 1; //그외에는 1을 리턴
}
//스테이지 완료화면
void ClearView() {
	char ch1;
	PlayerMoveAction(); //움직임 함수 호출
	if (return_bool) { // 만약 e를 눌렀을 경우 return
		return;
	}
	gotoxy(mX, mY + 3); //맵의 끝부분으로 이동
	printf("(Command)");
	printf("%3c", ch); // 입력받은 키 출력
	if (StageClear()) { // 클리어 확인

		if (userlevel < 4) { // 다음 스테이지 출력
			MapClear();
			rank_bool = 1;
			rankingcompare(userlevel);
			rankingsave(); //랭킹 저장
			rank_bool = 0;
			printf("%d Stage Clear!\n", userlevel + 1);
			printf("Let's go Next Stage!\n");

			userlevel++; // 다음 스테이지
			usercount = 0; // 움직임 횟수 초기화
			undoCount = 0;
			printf("Please press any key");
			ch1 = getch();
			if (ch1 != 0) {
				playerreset(); // 플레이어 위치 @ 확인
				return_bool = 0;
			}

		}
		else if (userlevel == 4) { // 모든 스테이지를 깼다면
			MapClear();
			rank_bool = 1;
			rankingcompare(userlevel);
			rankingsave(); //랭킹저장
			printf("★★★★★★You clear all stages!★★★★★★\n");
			printf("★★★★★★★★★★★Conglatulate★★★★★★★★★★★\n");
			return_bool = 1; // 시스템 종료
			return;
		}
		MapClear();
	}
}

//현재 스테이지 재시작
void Replay() {

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			map[userlevel][j][i] = stageData[userlevel][j][i]; //현재스테이지 맵 초기화
		}
	}
	playerreset(); // 플레이어 위치 @확인

	MapClear();
	drawMap();
	ClearView();
	undoCount = 0; // 언두 횟수 초기화
	return;
}
// 새로하기
void Newplay() {
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				map[k][j][i] = stageData[k][j][i]; // 모든 스테이지 초기화
			}
		}
	}

	MapClear();

	usercount = 0; //움직임 횟수 초기화
	undoCount = 5; // 언두 가능 횟수
	userlevel = 0; //레벨1에 해당하는 맵 출력
	playerreset(); // 플레이어 위치 @확인
	undoCount = 0; // 언두횟수 초기화
	MapClear();
	drawMap();
	ClearView();

	return;
}
// 소코반 파일 저장
void SokobanfileSave()
{
	FILE* sokobansave;
	MapClear();
	levelX;
	levelY;

	map[userlevel][levelY - 1][levelX - 1] = '@';// 사용자('@') 좌표에 해당하는 map 배열에 '@' 넣어주기


	sokobansave = fopen("sokoban.txt", "w");
	if (sokobansave == NULL)
	{
		printf("sokoban.txt File open Error!!\n");
		return;
	}
	fprintf(sokobansave, "%s\n", username); //username 저장
	fprintf(sokobansave, "%d\n", userlevel + 1); //userlevel 저장
	fprintf(sokobansave, "%d\n", usercount); //usercount 저장

	for (int i = userlevel; i < 5; i++) { //맵 저장
		fprintf(sokobansave, "%d\n", i + 1);
		for (int j = 0; j < 30; j++) {
			for (int k = 0; k < 30; k++) {
				fprintf(sokobansave, "%c", map[i][j][k]);

				if (map[i][j][k] == '\n' || map[i][j][k] == '\0') {
					break;
				}


			}
			if (map[i][j + 1][0] == '\0') {
				if (i == 4) {
					fprintf(sokobansave, "e"); //모든 맵이 끝났으면 e 넣어주기
				}
				break;
			}

		}
	}

	fclose(sokobansave);

	return;
}
void SokobanfileUproad() // 소코반 파일 업로드
{
	FILE* sokobanopen;
	char name[11];
	int count, level;
	int i;

	MapClear();


	sokobanopen = fopen("sokoban.txt", "r");

	if (sokobanopen != NULL)
	{
		fscanf(sokobanopen, "%s", name); //username 불러오기
		for (i = 0; i < 11; i++) // username에 저장
		{
			username[i] = name[i];
		}

		fscanf(sokobanopen, "%d", &level); //level 불러오기
		userlevel = --level; // --level 저장
		fscanf(sokobanopen, "%d", &count); // count 불러오기
		usercount = count; // usercount 에 저장


		char strTemp[30];
		int sa = 0;
		int i = 0, k;
		int num_$[5] = { 0, 0, 0, 0, 0 };
		int num_O[5] = { 0, 0, 0, 0, 0 };

		fgets(strTemp, sizeof(strTemp), sokobanopen);
		fgets(strTemp, sizeof(strTemp), sokobanopen);
		//strTemp에  sokoban.txt 에 있는 맵 저장
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

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 30; j++) {
				for (int z = 0; z < 30; z++) {
					map[i][j][z] = stageData[i][j][z];
					if (map[userlevel][j][z] == '@')
					{
						levelX = z + 1;
						levelY = j + 1;
					}
					if (map[i][j][z] == '\n' || map[i][j][z] == '\0') {
						break;
					}
				}
				if (map[i][j][0] == '\0') {
					break;
				}
			}
		}

		MapClear();


	}
	else //sokoban.txt 파일이 없는 경우
	{
		printf("저장된 sokoban.txt 파일이 없습니다.");
	}


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



// 언두 맵 저장
void UndoMap()
{
	for (int i = 4; i >= 0; i--) {
		for (int j = 0; j < 30; j++) {
			for (int k = 0; k < 30; k++) {
				undo[i][j][k] = undo[i - 1][j][k];//새로운 undomap을 저장하기 위해 배열을 한칸씩 뒤로 미루기
			}
		}
		undo[i];
		u_levelX[i] = u_levelX[i - 1];
		u_levelY[i] = u_levelY[i - 1];
	}

	for (int j = 0; j < 30; j++) {
		for (int k = 0; k < 30; k++) {
			undo[0][j][k] = map[userlevel][j][k];//undomap[0]에 변형되기전 가장 최근의 맵 상태 저장

		}
	}
	u_levelX[0] = levelX;
	u_levelY[0] = levelY;
}
// 언두 실행
void Undo()
{
	for (int j = 0; j < 30; j++) {
		for (int k = 0; k < 30; k++) {
			map[userlevel][j][k] = undo[0][j][k]; //map[userlevel]배열에 undo[0] 배열 저장
		}
	}
	levelX = u_levelX[0]; //사용자('@') X 좌표 undo맵의 '@' X 좌표로 설정
	levelY = u_levelY[0]; //사용자('@') Y 좌표 undo맵의 '@' Y 좌표로 설

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 30; j++) {
			for (int k = 0; k < 30; k++) {
				undo[i][j][k] = undo[i + 1][j][k]; //undo를 실행한 후 이전에 저장되어있던 undo맵을 가장 최근의 undo맵으로 가져오기 위해 배열을 한칸씩 앞당기기
			}
			undo[i][j];
		}
		u_levelX[i] = u_levelX[i + 1];
		u_levelY[i] = u_levelY[i + 1];
	}
	undoCount++;
}
//랭킹
void rankingcompare(int level)
{

	int i, j, k;
	rankinguproad();


	for (i = 0; i < 4; i++)
	{
		if (rankcount[level][i] > usercount || rankcount[level][i] == 0) // rankcount[level][i]보다 usercount가 작거나, rankcount[level][i] == 0 일때
		{
			for (j = 0; j < 4 - i; j++) // rankcount 한칸 뒤로 밀기
			{
				rankcount[level][4 - j] = rankcount[level][3 - j];
				for (k = 0; k < 11; k++) // rankname 한칸 뒤로 밀기
				{

					rankname[level][4 - j][k] = rankname[level][3 - j][k];


				}

			}
			for (k = 0; k < 11; k++) {
				rankname[level][i][k] = username[k]; // username , rankname에 넣기
			}
			rankcount[level][i] = usercount; //usercount , rankcount에 넣기
			break;
		}
	}
	if (rankcount[level][i] > usercount || rankcount[level][i] == 0) // rankcount[level][i]가 usercount보다 작거나, rankcount == 0일때
	{
		rankcount[level][i] = usercount; //rankcount 에 usercount 넣기


		for (k = 0; k < 11; k++)
		{
			rankname[level][i][k] = username[k]; // rankname 에 username에 넣기
		}
	}


}
//랭킹 보여주기
void rankingview(int level)
{
	char input = '?';
	int s;
	int i, j, k;
	MapClear();
	rank_bool = 1;



	if (rank_bool)
	{
		while (input != '\n')
		{

			if (level < 5) // 출력하고자 하는 level 이 0,1,2,3,4 일때 // 해당레벨
			{
				printf("Hello %s\n", username);
				printf("map %d\n", level + 1);
				if (level< userlevel)
				{
					rankinguproad();
				}
				else
				{
					rankingcompare(level); //level의 ranking 비교하기

				}
				for (j = 0; j < 3; j++)
				{

					for (k = 0; k < 11; k++)
					{


						if (rankname[level][j][0] == ' ' && rankname[level][j][1] == ' ' && rankname[level][j][2] == '\0')
						{
							s = 0; // rankname[level][j] 가 '  '일때 출력 x
							break;
						}

						else
						{
							s = 1; //rankname [level][j] 가 '  '가 아닐때 출력 o
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
				//level 5 , ranking 전체 출력
				printf("Hello %s\n", username);
				rankingcompare(userlevel);


				for (i = 0; i < 5; i++)
				{
					printf("map %d\n", i + 1);
					if (i != userlevel)
					{
						rankinguproad();
					}
					else
					{
						rankingcompare(i); //level의 ranking 비교하기

					}
					for (j = 0; j < 3; j++)
					{
						for (k = 0; k < 11; k++)
						{
							if (rankname[i][j][0] == ' ' && rankname[i][j][1] == ' ' && rankname[i][j][2] == '\0')
							{
								s = 0; // rankname[level][j] 가 '  '일때 출력 x
								break;
							}

							else
							{
								s = 1; //rankname [level][j] 가 '  '가 아닐때 출력 o
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
			printf("나가려면 엔터키를 누르세요.\n");

			gotoxy(mX, mY + 25);
			printf("(Command)");
			printf("%3c %c", ch, ch2);
			input = getch();
			MapClear();



		}
	}




	return;
}

void rankingreset()
{

	// rankingcount와 rankingname 초기화

	int i, j;
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
	int i, j;

	if (!rank_bool) // rankview를 실행하지 않고 ranking파일을  저장 하는 경우
	{
		rankingcompare(userlevel);

	}



	ranksave = fopen("ranking.txt", "w");

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)

		{
			// rankname이 '  '라면 '---'으로 ranking 파일에 저장
			if (rankname[i][j][0] == ' ' && rankname[i][j][1] == ' ' && rankname[i][j][2] == '\0')
			{
				fprintf(ranksave, "---");
			}
			//아니라면 원래 이름대로 저장
			else
			{
				fprintf(ranksave, "%s", rankname[i][j]);
			}
			fprintf(ranksave, " %d \n", rankcount[i][j]);

		}
	}



	fclose(ranksave);


}
//랭킹 불러오기
void rankinguproad()
{
	FILE* rankopen;
	int i, j, k;
	char name[11];
	int count;
	int ret;
	rankopen = fopen("ranking.txt", "r");

	if (rankopen == NULL) // ranking 파일이 없을 경우
	{
		rankingreset(); // ranking 초기화
		rankingsave(); // ranking파일 저장


	}


	rankopen = fopen("ranking.txt", "r");


	for (i = 0; i < 5; i++) // level
	{
		for (j = 0; j < 5; j++) //rank 1,2,3,4,5
		{
			ret = fscanf(rankopen, "%s %d", name, &count); // raning파일에서 name이랑 count 받아오기

			for (k = 0; k < 11; k++)
			{

				// ranking파일에서 불러온 name이 '---' 일 경우 '  '로 저장
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
				//ranking 파일에 불러온 name이 '---'아닐 경우name 저장
				rankname[i][j][k] = name[k];

			}
			rankcount[i][j] = count;
		}
	}

	fclose(rankopen);
	return;
}
