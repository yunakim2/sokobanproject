#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<termio.h>




FILE *rankopen ; //ranking 파일 open
FILE *ranksave ; //ranking 파일 save
FILE *sokobansave; //소코반 파일 save
FILE *sokobanopen; // 소코반 파일 open


int getch(void); //getch함수
void StartView(); // 초기 시작화면
void Login(); // user 이름 조건 검사 후 , username에 저장
void RankingSave(); //ranking 파일 저장
void RankingUproad(); // ranking 파일 data 저장
void RankingReset(); // ranking data 초기화
void RankingCompare(int level); // level 의 ranking data 비교
void LevelRanking(int level); // level 의 ranking 출력
int StageClear();//스테이지 완료 확인
void ClearView();//스테이지 완료 화면
void Replay();//재시작
void Newplay();
void loadMap();//맵 로드
void drawMap();//맵 출력
void displayHelp();
void PlayerMoveAction();//움직이기
void gotoxy(int, int);//원하는 좌표에 출력할수있게 하는  함수
void PrintInfo();//횟수
void SokobanfileSave(); // 소코반 파일 세이브
void SokobanfileUproad(); // 소코반 파일 업로드


char stageData[6][30][30];//맵 입력받기
char map[30][30];//스테이지별 맵 출력하기위해 사용
int levelX, levelY;//좌표

char rankname[5][5][10]; //level별 상위 5명의 ranking data 이름
int rankcount[5][5]; // level별 상위 5명의 ranking data count 갯수

char tempname[2][10] ; // count 비교를 위한 name 임시 저장소
int tempcount[2]; // count 비교를 위한 count 임시 저장소

char username[10] ; // user 이름
char inputname[10];  // input data
int usercount[5]={0,0,0,0,0};
int userlevel = 0;

//메인
int main()
{	
	StartView();
	loadMap();

	int input;
	
	userlevel=0; //레벨1에 해당하는 맵 출력
	while(1)
	{
		memcpy(map, stageData[userlevel], sizeof(map));
		for (int y = 0; y < 30; y++)
		{
			for (int x = 0; x < 30; x++)
			{
				if (map[y][x] == '@')
				{
					levelX = x;
					levelY = y;
					map[y][x] = ' ';
				}
			}
		}

		system("clear");

		while(1)
		{
			drawMap();
			PlayerMoveAction();
		}
	}
	input = getch();

	return 0;
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
	int length ;
reinput : while(1)
	{
		length = 0;
		printf("input name : ");
		scanf("%s",inputname);
		length = strlen(inputname);
		for( int i = 0 ; i<length ; i++)
		{

			if(!( (inputname[i]>=65 && inputname[i]<=90) || (inputname[i]>=97&& inputname[i]<=122)))
			{
				printf("영문자만 가능합니다. \n");
				goto reinput;
			}
		}

		if( length>10)
		{
			printf("영문자 최대 10문자 까지 가능합니다.\n");
			printf("다시 입력해주세요 ! \n");
		}

		else
		{
			for(int i = 0; i<length; i++)
			{
				username[i] = inputname[i];
			}
			break;
		}

	}
	return ;
}
//맵
void loadMap() {
	FILE *pFile = NULL;

	pFile = fopen("map.txt", "r");
	if (pFile != NULL)
	{
		char strTemp[30];
		char *pStr;

		int sa = 0;
		int i;
		int num_$[5] = {0, 0, 0, 0, 0};
		int num_O[5] = {0, 0, 0, 0, 0};

		i = 0;
		fgets(strTemp, sizeof(strTemp), pFile);
		while(strTemp[0] != 50)
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

void drawMap()
{
	int mapX, mapY;
	for (mapY = 1; mapY < 31; mapY++)
	{
		for (mapX = 1; mapX < 31; mapX++)
		{
			if(map[mapY-1][mapX-1] == '\0') {
				break;
			}
			gotoxy(mapX, mapY);			
			putchar(map[mapY-1][mapX-1]);
			/*if (map[mapY][mapX] == '\0') {
				break;
			}*/
		}
		/*if (map[mapY][mapX] == '\n') {
			break;
		}*/
	}
	gotoxy(levelX, levelY);
	putchar('@');
}

void PlayerMoveAction()
{
	int dx, dy;
	char ch;

	ch=getchar();
	
	if(ch=='e')
	{
		exit(0);
	}
	else if(ch == 'r'||ch =='R')
	{
		Replay();
	}

	else if(ch=='h'&&ch=='j'&&ch=='k'&&ch=='l')
	{
		ch=getchar();
		switch(ch)
		{
			case 'h':
				dx = -1; dy = 0; break;
			case 'j':
				dx = 0; dy = 1; break;
			case 'k':
				dx = 0; dy = -1; break;
			case 'l': 
				dx = 1; dy = 0; break;
		}
		if (levelY+dy>=0&&levelX+dx>=0)
		{
		if (map[levelY+dy][levelX+dx] == '#')
		{
			return;
		}
		}
		if (map[levelY+dy][levelX+dx] == '0')
		{
			if (stageData[userlevel][levelY+dy*2][levelX+dx*2] = ' ')
			{
				map[levelY+dy][levelX+dx] = ' ';
				map[levelY+dy*2][levelX+dx*2] = '0';
			}
			else if (stageData[userlevel][levelY+dy*2][levelX+dx*2] == '.')
			{
				map[levelY+dy][levelX+dx] = '.';
				map[levelY+dy*2][levelX+dx*2] = '0';
			}
			else if (stageData[userlevel][levelY+dy*2][levelX+dx*2] == '#')
			{
				return;
			}
		}
		

		levelX += dx;
		levelY += dy;
		usercount[userlevel];//userlevel ++;
	}
}

void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}

void PrintInfo()//int NumMove필요
{
	gotoxy(59,2); printf(" S O K O B A N");

	gotoxy(61,5); printf("스테이지 : %d", 5 - 1);
	gotoxy(61,7); printf("움직인 횟수 : %d", usercount[userlevel]);

	gotoxy(67,10); printf("UP");
	gotoxy(67,11); printf("k");
	gotoxy(60,12); printf("LEFT h   l RIGHT");
	gotoxy(67,13); printf("j");
	gotoxy(66,14); printf("DOWN");

	gotoxy(61,16); printf("다시하기 : R");
}

void displayHelp() {
	//char input;

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
   //input = linux_kbhit();

}
//량킹
void LevelRanking(int level)
{
	RankingCompare(level);

	 printf(" map %d\n", level+1);

		for( int j = 0; j<5 ; j++)
		{
		 printf("%-10s",rankname[level][j]);
		 printf(" %d\n",rankcount[level][j]);
		}
	return ;
}
//랭킹
void RankingCompare(int level)
{
	RankingUproad();

	for(int i = 0; i<5; i++)

	{
		if(usercount[level]>rankcount[level][i])
		{
			strcpy(tempname[0], rankname[level][i]);
			tempcount[0] = rankcount[level][i];

			strcpy(rankname[level][i],username);
			rankcount[level][i] = usercount[level] ;


			for(int j = i+1 ; j<5 ; j++)
			{
				strcpy(tempname[1], rankname[level][j]);
				tempcount[1] = rankcount[level][j];

				strcpy(rankname[level][j], tempname[0]);
				rankcount[level][j] = tempcount[0];

				strcpy(tempname[0],tempname[1]);
				tempcount[0] = tempcount[1] ;
			}
			break;
		}
	}

	return ;
}
//랭킹
void RankingReset()
{
	 for(int i = 0; i<5 ; i++)
	 { for(int j =0; j<5 ; j++)
         {
              strcpy(rankname[i][j],"  ---");
              rankcount[i][j] = 0;
          }
	 }

	 return ;
}
//랭킹
void RankingSave()
{
	int length;
	ranksave = fopen("ranking.txt","w");
	for(int i =0 ; i<5; i++)
	{
		RankingCompare(i);
	}

  for(int i = 0; i<5 ; i++)
    {   fprintf(ranksave,"map %d\n",i+1);
		for( int j = 0; j<5 ; j++)
         {
		 length =0 ;
		 length = strlen(rankname[i][j]);
		 for(int k =0 ; k<length ; k++)
		 {
			 fprintf(ranksave,"%c",rankname[i][j][k]);
		 }
		 fprintf(ranksave, " %d\n",rankcount[i][j]);
		 }
	 }
	 fclose(ranksave);
		return ;
}
//랭킹업로드
void RankingUproad()
{
	rankopen = fopen("ranking.txt","rt");
	int ret;
	char tempn[10];
	int tempc;

	if ( rankopen == NULL)
	{
	RankingReset();
	RankingSave();
	}
	rankopen = fopen("ranking.txt","rt");
	while(1)
	{	for(int i = 0 ; i<5 ; i++)
		{for(int j = 0; j<5 ; )
			{
				ret = fscanf(rankopen,"%s %d",tempn, &tempc);
				if(!(strcmp(tempn,"map")))
				{
					;
				}

				else
				{
					for(int k = 0 ; k<10 ; k++)
					{
						rankname[i][j][k] = tempn[k];
					}
					rankcount[i][j] = tempc;
					j++;
				}

			}
			if(ret==EOF) break;

		}
		if(ret == EOF) break;
	}
	fclose(rankopen);

	return ;
}

//스테이지 완료되었는지 확인
int StageClear(){
  int x, y;
  for(x = 0; x < 20; x++){
    for(y = 0; y < 18; y++){
      if(stageData[userlevel][x][y] == '.' && map[x][y] != 0){
        return 0 ;
      }
    }
  }
  return 1 ;
}
//스테이지 완료화면
void ClearView(){
	  //Printinfo(); // 정보출력 함수 <- 나중에 바꿔주세욤
	  //PlayerMoveAction(); // 플레이어 이동 함수 <- 나중에 바꿔주세욤

	  if(StageClear()){ // 클리어 확인

	    if(userlevel < 4){ // 다음 스테이지 출력
	      printf("%d Stage Clear!\n", userlevel+1);
	      printf("Let's go Next Stage!\n");

	      userlevel++;
		  usercount[userlevel] = 0;
		  RankingSave();

	    }
	    else if(userlevel == (4)){
	      printf("★★★★★★You clear all stages!★★★★★★\n");
	      printf("★★★★★★★★★★★Conglatulate★★★★★★★★★★★\n");
				RankingSave();
	      exit(0);
	    }
	  }
	}

//재시작
void Replay(){

  return ;
}

void Newplay(){
	for(int i = 0; i<5;i++){
		usercount[i] = 0;
	}

	return ;
}
// 소코반 파일 저장
 void SokobanfileSave()
{

	sokobansave = fopen("sokoban.txt","w");
	if(sokobansave == NULL)
	{
		printf("sokoban.txt File open Error!!\n");
		return;
	}
	fprintf(sokobansave,"username %s\n",username);
	fprintf(sokobansave,"userlevel %d\n",userlevel);
	fprintf(sokobansave,"count %d\n",usercount[userlevel]);
	
	fclose(sokobansave);
	RankingSave();
	return ;
}

void SokobanfileUproad() // 소코반 파일 업로드
{
	int ret;
	char temp1[10];
	char temp2[10];
	int tempc;
	int templ;
	sokobanopen = fopen("sokoban.txt","r");

	if(sokobanopen ==NULL)
		{
			printf("sokoban.txt File open Error!!\n");
			exit(0);
		}
	
	ret = fscanf(sokobanopen,"%s %s",temp1,temp2);
	if(strcmp(temp1,"username"))
	{
		for(int k =0 ; k<10 ; k++)
		{
			username[k] = temp2[k];
		}
	}
	ret = fscanf(sokobanopen,"%s %d",temp1,templ);
	if(strcmp(temp1,"userlevel"))
	{
		userlevel = templ;
	}
	ret = fscanf(sokobanopen,"%s %d",temp1,tempc);
	if(strcmp(temp1,"count"))
	{
		usercount[userlevel] = tempc;
	}




	return;

}
int getch(void)
{
	int ch;
	struct termios buf;
	struct termios save;

	tcgetattr(0,&save);

	buf = save;

	 buf.c_lflag&=~(ICANON|ECHO);
     buf.c_cc[VMIN] = 1;
     buf.c_cc[VTIME] = 0;

     tcsetattr(0, TCSAFLUSH, &buf);
 
     ch = getchar();
     tcsetattr(0, TCSAFLUSH, &save);
 
     return ch;
  }
