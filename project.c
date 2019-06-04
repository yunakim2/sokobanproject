

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<termio.h>

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
void Newplay();
void loadMap();//맵 로드
void drawMap();//맵 출력
void displayHelp();
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
_Bool rank_bool=0; 
_Bool return_bool = 0;
int dx, dy; //플레이어 이동

char username[11]; // user 이름
char inputname[11];  // input data
int usercount;
int userlevel = 0;

int undosaveCount; // 언두 맵 저장 횟수
int undoCount; // 언두 가능 횟수

char ch; //키 입력
int mX, mY; // 맵 끝부분 위치

//메인
int main()
{
   StartView();
   loadMap();

   int input;

   userlevel = 2; //레벨1에 해당하는 맵 출력
   while (1)
   {
      //memcpy(map, stageData[userlevel], sizeof(map));
      //playerreset();
	for(int i = 0; i<5; i++) {
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
}

void playerreset() {
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
         printf("영문자만 가능합니다. \n");
         goto reinput;
      }
   }

   if (length > 11)
   {
      printf("영문자 최대 10문자 까지 가능합니다.\n");
      printf("다시 입력해주세요 ! \n");
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


       input = getch();
       MapClear();
       return;
}
//맵
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
   for (mapY = 1; mapY < 31; mapY++)
   {
      for (mapX = 1; mapX < 31; mapX++)
      {
         if (map[userlevel][mapY - 1][mapX - 1] == '\0') {
            break;
         }
         gotoxy(mapX, mapY+2);
         putchar(map[userlevel][mapY - 1][mapX - 1]);

      }
   }
   mX = mapX;
   mY = mapY;
   gotoxy(levelX, levelY+2);
   putchar('@');
   gotoxy(1, 1);
   printf("Hello %s", username);
   gotoxy(mapX, mapY);
   printf("(Command)");
   printf("%3c", ch);
}

void PlayerMoveAction()
{
   int dx = 0, dy = 0;
   char ch1;

   ch1 = getch();
   ch = ch1;

   switch (ch1)
   {
   case 'h':
   case 'H':
      //UndoMap();//undo맵 저장
      usercount++;
      dx = -1; dy = 0; 
      return_bool = 0;
      break;
   case 'j':
   case 'J':
      //UndoMap();//undo맵 저장
      usercount++;
      dx = 0; dy = 1; 
      return_bool = 0;
      break;
   case 'k':
   case 'K':
      //UndoMap();//undo맵 저장
      usercount++;
      dx = 0; dy = -1; 
      return_bool = 0;
      break;
   case 'l':
   case 'L':
      //UndoMap();//undo맵 저장
      usercount++;
      dx = 1; dy = 0; 
      return_bool = 0;
      break;
   }
   if (((((((ch != 'h' && ch != 'j') && ch != 'k') && ch != 'l') && ch != 'H') && ch != 'J') && ch != 'K') && ch != 'L')
   {
      Option(ch);
   }

   // 충돌 체크
   if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == '#') // 앞에 '#'벽이 있으면
   {
      dx = 0; // 움직이지 않음
      dy = 0;
   }
   if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == '$') // '$'상자를 만난다면
   {
      UndoMap();
      if (map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == '.') // 그 앞이 공백이라면
      {
         map[userlevel][levelY - 1 + dy][levelX - 1 + dx] = '@'; // 움직인 후 플레이어 좌표 저장
         map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] = '$'; // 움직인 후 상자 좌표 저장
      }
      else if (map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == '#' || map[userlevel][levelY - 1 + 2 * dy][levelX - 1 + 2 * dx] == '$') // 플레이어가 상자를 밀고 있을때 상자 앞이 # 이거나 $ 이라면
      {
         dx = 0; // 움직이지 않음
         dy = 0;
      }

   }
   if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == '.') // 플레이어가 움직인다면
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
   if (map[userlevel][levelY - 1 + dy][levelX - 1 + dx] == 'O') // 'O'를 만난다면
   {
      if (stageData[userlevel][levelY - 1][levelX - 1] == 'O') // 원래 맵에서 'O'였으면
      {
         map[userlevel][levelY - 1 + dy][levelX - 1 + dx] = 'O'; // 'O' 계속 유지
      }  //
      UndoMap();//
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

   gotoxy(mX, mY);
   printf("(Command)");
   printf("%3c", ch);
   input = getch();
   if (input != 0) {
      return;
   }
}

//스테이지 완료되었는지 확인
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
//스테이지 완료화면
void ClearView() {
   char ch1;
   PlayerMoveAction();

   if (StageClear()) { // 클리어 확인

      if (userlevel < 4) { // 다음 스테이지 출력
         MapClear();
         printf("%d Stage Clear!\n", userlevel + 1);
         printf("Let's go Next Stage!\n");


         rankingsave();
         userlevel++;
         usercount = 0;
         printf("Please press any key");
         ch1 = getch();
         if (ch1 != 0) {
            playerreset();
            return_bool = 0;
         }

      }
      else if (userlevel == 4) {
         MapClear();
         printf("★★★★★★You clear all stages!★★★★★★\n");
         printf("★★★★★★★★★★★Conglatulate★★★★★★★★★★★\n");
         rankingsave();
         return_bool = 1;
         return;
      }
      MapClear();
   }
}

//재시작
void Replay() {
   //memcpy(map, stageData[userlevel], sizeof(map));
   while (1)
   {
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

      //playerreset();

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
   //memcpy(map, stageData[userlevel], sizeof(map));
   MapClear();

   usercount = 0;
   undoCount = 5; // 언두 가능 횟수
   userlevel = 0; //레벨1에 해당하는 맵 출력
   while (1)
   {
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
		
      //playerreset();

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
// 소코반 파일 저장
void SokobanfileSave()
{
   FILE* sokobansave;
   char input;
   MapClear();
   levelX;
   levelY;

   map[userlevel][levelY - 1][levelX - 1] = '@';

   //input = getch();


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
               fprintf(sokobansave, "e");
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
		
      //}

      MapClear();


   }
   else
   {
      printf("저장된 sokoban.txt 파일이 없습니다.");
   }

   printf("파일 업로드\n");
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



// 언두 맵 저장
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
// 언두 실행
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
//랭킹
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
   int ch1;
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
         printf("나가려면 아무키나 누르시오.\n");

         gotoxy(mX, mY);
         printf("(Command)");
         printf("%3c", ch);

         ch1 = getch();

         if (ch1)
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
               //printf("--- 저장\n");
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
