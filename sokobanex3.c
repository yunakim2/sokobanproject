/*ranking level 다시 수정 필요 , ranking 저장파일 수정필요*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login(); //inputname을 받는 함수
void startview(); // 게임 시작 화면 출력 함수
void savefile(); // sokoban 파일 저장함수
void inputkeybord(); // 키보드 input 함수
void rankingopen(); // ranking 출력 함수
void rankingsave(); // ranking 저장 함수
void rankingcompare(); // 움직인 횟수 순위 비교 함수

#define MAX_NAME_LENGTH 10
#define RANK_SIZE 5

char inputname[MAX_NAME_LENGTH]; // inputname 저장
FILE *save; 
FILE *rankopen;
FILE *ranksave;
int usercount = 0; // 움직인횟수

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
			if((inputname[i]>= 65 && inputname[i]<= 90) || (inputname[i]>=97				 && inputname[i]<=122) || inputname[i] == '\0')
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
	char c;
	while(1)
	{ c = getchar(); // 수정 필요
	  getchar(); //null문자 지우는 용도 수정 필요 _ 한문자만 받도록 
	  //myflush() 구현 필요
	 switch(c)
		{
			case 'h' :
				userdata.count++; //test용
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
				savefile ();
			break;
			case 'f' :
				break;
			case 'd' :
				break;
			case 'r' :
				break;
			case 't' :
				rankingopen(); //수정 필요함!!! ,t만 전체순위,
					  		   // t다음 숫자 오면 해당 맵 순위
				break;
			case 's' :
				savefile();
				break;
			
			default : 
				printf("다른키를 입력하세요\n");
				break;
			}
	 if(c=='e'){exit(0);}
	}
	return;
}
void rankingopen()
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
		for(int i =0 ; i<RANK_SIZE ; i++)
		{
			fscanf(rankopen, "%d %s %d",totalrankdata[i].rank,totalrankdata[i].name, totalrankdata[i].count);
		}
	}
	
	 fprintf(ranksave,"-------------------------------------------\n");
     fprintf(ranksave,"레벨   순위        이름         움직인 횟수 \n");
     fprintf(ranksave,"-------------------------------------------\n");
  for( int i = 0; i<5 ; i++)
     {

         printf("%-3d %-3d %-8s %-7d\n\n",rankdata[i].level, rankdata[i].rank,rankdata[i].name, rankdata[i].count);

     }
     fprintf(ranksave,"-------------------------------------------\n");
	
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

