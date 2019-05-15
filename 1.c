#include<stdio.h>

#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAXSTAGE 5
#define MAX_NAME_LENGTH 10

//함수 선언
void login(); //로그인
void startview(); //로딩
void DrawStage(); //맵 불러오기
void PlayerMoveAction(); //플레이어 이동
BOOL StageClear(); // 스테이지 완료
void Printinfo(); //게임정보출력
void Re(); //재시작

//전역변수 선언
char Stage[18][21];
char inputname[MAX_NAME_LENGTH];

int RoundNum;
int Roundx, Roundy;
int NumMowe;
int Restart;


//로딩화면 출력
void startview(){
  printf("sokoban\n");
	printf("Start....\n");
	printf("\n\n");

	login();
	return ;
}

//로그인
void login(){
  int i =0, length = 0;
	reinput : 	while(1)
	{
		printf("input name : ");
		gets(inputname);
		length = strlen(inputname);


		// printf("inputname [0] = %c", inputname[0]);

		for(i =0; i<=length ; i++)
		{
		  printf("inputname[i] : %c\n",inputname[i]);
			if((inputname[i]>= 65 && inputname[i]<= 90) || (inputname[i]>=97 && inputname[i]<=122) ||
					inputname[i] == '\0')
			{
				if(inputname[i] == '\0') {break;}

				continue;
			}

			else
			{
				printf("영문자만 입력가능합니다. 다시 입력해주세요.\n");
				goto reinput;
			}

		}
		if(inputname[i] == '\0') {break;}
	    if(length >MAX_NAME_LENGTH)
		{
			printf("inputname은 영문 최대 10문자만 가능합니다. 다시 입력해주세요. \n");

			goto reinput ;
		}


	}
	printf("Hello %s\n",inputname);
	return ;
}

//맵 불러오기
void DrawStage(){
  /*이부분 채워주세욤*/
}

//플레이어 이동
void PlayerMoveAction(){
  /* 이부분 채워주세욤! */
  //ESC키 눌렀을 때
  if( ch == ESC ){
    exit(0);
  }
  //r이나 R키 눌렀을 때
  else if(ch == 'r' || ch == 'R'){
    Re();
  }
}

//게임정보 출력
void Printinfo(){
  /*이부분 채워주세욤*/
}

//스테이지 완료
BOOL StageClear(){
  int x, y;
  for(x = 0; x < 20; x++){
    for(y = 0; y < 18; y++){
      if(MapData[RoundNum][x][y] == '.' && Stage[x][y] != 0){
        return FALSE;
      }
    }
  }
  return TRUE;
}
//재시작
void Re(){
  Restart = 1;
}
//메인함수
int main(void){
  LoadingStage();
  RoundNum = 0;
//4번 6번 파트
while (1) {
  DrawStage();
  Printinfo();
  PlayerMoveAction();
  if(Restart == 1){ // 재시작
    Restart = 0;
    break;
  }
  if(StageClear()){ // 클리어 확인
    clrscr();
    if(RoundNum < MAXSTAGE - 1){ // 다음 스테이지 출력
      printf("%d Stage Clear!\n", RoundNum+1);
      printf("Let's go Next Stage!\n");
      delay(3500);
      RoundNum++;
      break;
    }
    else if(RoundNum == (MAXSTAGE - 1)){
      printf("★★★★★★You clear all stages!★★★★★★\n");
      printf("★★★★★★★★★★★Conglatulate★★★★★★★★★★★")

    }
  }
}
  getch();
  return 0;
}
