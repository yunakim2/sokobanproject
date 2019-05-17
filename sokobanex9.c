/*ranking level 다시 수정 필요 , ranking 저장파일 수정필요*/
/*inputkeybord 수정 필요할 것 같습니다ㅜㅜ*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login(); //inputname을 받는 함수
void startview(); // 게임 시작 화면 출력 함수
void savefile(); // sokoban 파일 저장함수
void inputkeybord(); // 키보드 input 함수
void totalrankingopen(); // totalranking 출력 함수
void levelrankingopen(char c); // char c level 출력함수
void rankingsave(); // ranking 저장 함수
void rankingcompare(); // 움직인 횟수 순위 비교 함수
int StageClear(); // 스테이지 완료
void ClearView(); //스테이지 완료 함수 출력
void Re(); //재시작
void myflush(); // 입력버퍼 모두 지우는 함수

/*플레이어 이동부분 맨아래 부분 확인해서 변경해주세요 - 완료 */
/*메인함수에 함수이름 임의로 쓴거 있으니 확인해주세요*/

#define MAX_NAME_LENGTH 10
#define RANK_SIZE 5
#define MAXSTAGE 5 // 실행시키려고 만든 임의의값

char inputname[MAX_NAME_LENGTH]; // inputname 저장
FILE *save;
FILE *rankopen;
FILE *ranksave;
int usercount = 0; // 움직인횟수
int Restart; //재시작 확인용
char MapData[MAXSTAGE][18][21]={0};//맵 불러오기 데이터 - 나중에 수정
char Stage[18][21]={0};//현재 스테이지 진행상황 - 나중에 수정
int RoundNum;//스테이지 레벨 - 나중에 수정 가능
typedef struct rankdata
{
	int level;
	char name[10];
	int count ;
	int rank ;
} Rankdata;

typedef struct totalrankdata
{
	char name[10];
	int count;
	int rank;
}Totalrankdata;

typedef struct userdata
{
	char level;
	char name[10];
	int count;
	int rank;
}Userdata ;

Totalrankdata totalrankdata[RANK_SIZE+1];
Rankdata rankdata[RANK_SIZE+1];
Userdata userdata;


int main(void)
{
	startview();
	/*임의로 배열에 값대입했습니다. 나중에 바꿔주세욤*/
	for (int i = 0; i <18; i++){
    for (int t = 0; t < 21; t++) {
      Stage[i][t] = 'a';
    }
  }
  for (int i = 0; i <18; i++){
    for (int t = 0; t < 21; t++) {
      MapData[RoundNum][i][t] = '1';
    }
  }
	/********************************************************/
	ClearView();

	return 0;
}

void startview()
{
	printf("sokoban\n");
	printf("Start....\n");
	printf("\n\n");

	login();
	return ;
}
void login()
{
	int i =0, length = 0;
	reinput : 	while(1)
	{
		printf("input name : ");
		gets(inputname);
		length = strlen(inputname);


		// printf("inputname [0] = %c", inputname[0]);

		for(i =0; i<=length ; i++)
		{
		  //printf("inputname[i] : %c\n",inputname[i]);
			if((inputname[i]>= 65 && inputname[i]<= 90) || (inputname[i]>=97&& inputname[i]<=122) || inputname[i] == '\0')
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
	memcpy(userdata.name , inputname, sizeof(inputname));
	userdata.count =0;
	userdata.level =1;
	inputkeybord();
	return ;
}
void inputkeybord()
{
	char c,ch;
	while(1)
	{ c = getchar(); // 수정 필요
	  ch = getchar();

	  if ( ch == '\n')
	  {
		  myflush();
	  }

	 switch(c)
		{
			case 'h' :
				userdata.count++; //test용****playermoveaction구현
				break;
			case 'j' :
				userdata.count++; // test용
				break;
			case 'k' :
				userdata.count++; //test용
				break;
			case 'l' :
				userdata.count++; //test용
				break;
			case 'n' :
				break;
			case 'e' :
				printf("B Y E %s ... \n",userdata.name);
				savefile ();
				break;
			case 'f' :
				break;
			case 'd' :
				break;
			case 'r' :
				Re();
				break;
			case 't' :
				totalrankingopen(); //수정 필요함!!! ,t만 전체순위,

				 if(c=='t' && (ch != '\n')){

           				levelrankingopen(ch);
						myflush();
						}
				break;
			case 's' :
				savefile();
				break;

			default :
				printf("다른키를 입력하세요\n");
				break;
		}
	}
	if(c=='e'){exit(0);}

	return;
}

void levelrankingopen(char c)
{

	rankopen = fopen("ranking.txt","r");
	if(rankopen == NULL)
	{
		printf("rankng 파일 열기 실패 ! \n");
		return;
	}
	while(1)
	{

		if(feof(rankopen))
			break;
		for(int i =0; i<RANK_SIZE ; i++)
		{
			fscanf(rankopen, "%d %d %s %d", rankdata[i].level, rankdata[i].rank, rankdata[i].name , rankdata[i].count);

		}

	}

	 printf("***********map %c 순위 입니다.*************\n");
	 printf("-------------------------------------------\n");
     printf("   순위        이름         움직인 횟수 \n");
     printf("-------------------------------------------\n");
  for( int i = 0; i<5 ; i++)
     {

         printf("%-3d %-3d %-8s %-7d\n\n",rankdata[i].level, rankdata[i].rank,rankdata[i].name, rankdata[i].count);

     }
     printf("------------------------------------------\n");

	fclose(rankopen);
	return ;
}
void totalrankingopen()
{
	rankopen = fopen("ranking.txt","r");
	if(rankopen == NULL)
	{
		printf("ranking 파일 열기 실패 !\n");
		return ;
	}
	while(1)
	{
		if(feof(rankopen))
			break;
		for(int i =0 ; i<RANK_SIZE ; i++)
		{
			fscanf(rankopen, "%d %s %d", totalrankdata[i].rank, totalrankdata[i].name, totalrankdata[i].count);
		}
		 printf("*********** total 순위 입니다.*************\n");
         printf("-------------------------------------------\n");
         printf("   순위        이름         움직인 횟수 \n");
         printf("-------------------------------------------\n");


	  for( int i = 0; i<5 ; i++)
	      {

	           printf(" %-3d     %-10s      %-7d\n\n",totalrankdata[i].rank,totalrankdata[i].name,totalrankdata[i].count);

	      }
	    printf("------------------------------------------\n");
	}
	   fclose(rankopen);
	   return ;


}
void rankingsave()
{
	ranksave = fopen("ranking.txt","w");
	rankingcompare();
	fprintf(ranksave,"ranking 저장 파일 입니다.\n");
	fprintf(ranksave,"-------------------------------\n");
	fprintf(ranksave,"레벨  순위   이름   움직인 횟수 \n");
	fprintf(ranksave,"-------------------------------\n");
	for( int i = 0; i<5 ; i++)
	{

		fprintf(ranksave, " %d    %d %-10s      %-7d\n\n",rankdata[i].level, rankdata[i].rank,rankdata[i].name, rankdata[i].count);


	}
	fprintf(ranksave,"--------------------------------\n");
	fprintf(ranksave,"            totalrank           \n");
	fprintf(ranksave,"--------------------------------\n");
	fprintf(ranksave,"순위       이름      움직인 횟수\n");
	fprintf(ranksave,"--------------------------------\n");
	for(int i =0; i<5; i++)
	{
		fprintf(ranksave," %-3d     %-10s      %-7d\n\n",totalrankdata[i].rank,totalrankdata[i].name,totalrankdata[i].count);
	}

	fprintf(ranksave,"--------------------------------\n");
	fclose(ranksave);
	printf("raking 파일이 저장되었습니다.\n");
	return ;

}

void rankingcompare()
{

	memcpy(rankdata[5].name, userdata.name , sizeof(userdata.name));
	memcpy(totalrankdata[0].name, rankdata[0].name , sizeof(rankdata[0].name));
	memcpy(totalrankdata[5].name, userdata.name , sizeof(userdata.name));

	rankdata[5].count =userdata.count;
	rankdata[5].level = userdata.level;

	totalrankdata[0].count = rankdata[0].count ;
	totalrankdata[0].rank = 1;
	totalrankdata[5].count = userdata.count;


	for(int i = 0 ; i<RANK_SIZE+1 ; i++)
	{
		rankdata[i].rank =1;
		for(int j = 0; j<RANK_SIZE+1 ; j++)
		{
			if(rankdata[i].count < rankdata[j].count)
			{
				rankdata[i].rank++;
			}
			else if(rankdata[i].count == rankdata[j].count)
			{
				if(i<j)
				{
					rankdata[j].rank++;
				}
			}
		}
	}

	for(int i =0; i<RANK_SIZE ;i++)
	{
			for(int j =0 ; j<RANK_SIZE+1 ; j++)
			{
				if(totalrankdata[i].count > rankdata[j].count)
				{
			        memcpy(totalrankdata[i].name, rankdata[i].name , sizeof(userdata.name));

					totalrankdata[i].count = rankdata[i].count;
				}
			}
	}



	return ;
}
void savefile()
{
	save = fopen("sokoban.txt","w");
	if(save ==NULL)
	{
		printf("sokoban.txt File open Error!!\n");
		return ;
	}
	fprintf(save,"******* %s의 소코반 파일 입니다. ********\n",inputname);
	fprintf(save,"inputname : %s, total count : %d , level : %d ",userdata.name, userdata.count, userdata.level);


	fclose(save);
	rankingsave();
	printf("소코반 파일이 저장되었습니다.\n");

	return ;
}
//플레이어 이동
void PlayerMoveAction()
{
	; // 구현 필요
	return ;
}

//스테이지 완료되었는지 확인
int StageClear(){
  int x, y;
  for(x = 0; x < 20; x++){
    for(y = 0; y < 18; y++){
      if(MapData[RoundNum][x][y] == '.' && Stage[x][y] != 0){
        return 0 ;
      }
    }
  }
  return 1 ;
}
//스테이지 완료 화면 출력
void ClearView(){
	RoundNum = 0;
	while (1) {
	  //DrawStage(); //스테이지 출력 함수 <- 나중에 바꿔주세욤
	  //Printinfo(); // 정보출력 함수 <- 나중에 바꿔주세욤
	  //PlayerMoveAction(); // 플레이어 이동 함수 <- 나중에 바꿔주세욤
	  if(Restart == 1){ // 재시작
	    Restart = 0;
	    break;
	  }
	  if(StageClear()){ // 클리어 확인

	    if(RoundNum < MAXSTAGE - 1){ // 다음 스테이지 출력
	      printf("%d Stage Clear!\n", RoundNum+1);
	      printf("Let's go Next Stage!\n");

	      RoundNum++;
	      break;
	    }
	    else if(RoundNum == (MAXSTAGE - 1)){
	      printf("★★★★★★You clear all stages!★★★★★★\n");
	      printf("★★★★★★★★★★★Conglatulate★★★★★★★★★★★\n");

	      exit(0);
	    }
	  }
	}
}
//재시작
void Re(){
  Restart = 1;
  return ;
}
// stdin 입력 버퍼 모두 지우기
void myflush()
{
	while(getchar() != '\n')
	{
		;
	}
	return ;

}
