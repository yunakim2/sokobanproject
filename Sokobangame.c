#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *rankopen ; //ranking 파일 open
FILE *ranksave ; //ranking 파일 save

void StartView(); // 초기 시작화면
void Login(); // user 이름 조건 검사 후 , username에 저장 
void RankingSave(); //ranking 파일 저장
void RankingUproad(); // ranking 파일 data 저장
void RankingReset(); // ranking data 초기화
void RankingCompare(int level); // level 의 ranking data 비교
void LevelRanking(int level); // level 의 ranking 출력

char rankname[5][5][10]; //level별 상위 5명의 ranking data 이름
int rankcount[5][5]; // level별 상위 5명의 ranking data count 갯수

char tempname[2][10] ; // count 비교를 위한 name 임시 저장소
int tempcount[2]; // count 비교를 위한 count 임시 저장소

char username[10] ; // user 이름
char inputname[10];  // input data
int usercount[5]={0,0,0,0,0};
int userlevel = 0;

int main()
{


	return 0;
}

void StartView()
{
	printf("sokoban\n");
	printf("start .... \n");

	Login();
	return;
}

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
void RankingSave()
{
	int length;
	ranksave = fopen("ranking.txt","w");


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
