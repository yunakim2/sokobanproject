#include<stdio.h>

#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAXSTAGE 5

//함수 선언
void LoadingStage();
void DrawStage();
void PlayerMoveAction();
BOOL StageClear(); // 스테이지 완료함수
void Printinfo();
void Re(); //재시작

//전역변수 선언
char Stage[18][21];

int RoundNum;
int Roundx, Roundy;
int NumMowe;
int Restart;

//로딩화면 출력
void LoadingStage(){
  /*이부분 채워주세욤*/
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
    printf("%d Stage Clear!\n", RoundNum+1);
    printf("Let's go Next Stage!\n");
    delay(3500);
    if(RoundNum < MAXSTAGE - 1){ // 다음 스테이지 출력
      RoundNum++;
    }
    break;
  }
}
  getch();
  return 0;
}
