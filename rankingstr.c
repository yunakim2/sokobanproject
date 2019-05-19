#include<stdio.h>
#include<string.h>
#include<stdlib.h>


FILE *rankopen;
FILE *ranksave;

void startview();
void login();
void rankingopen();
void rankingsave();
void rankingUproad();
void rankingreset();
void rankingcompare(int level);
void levelranking(int level);
void arrayCopy(char dst[], const char src[], int n );

char rankname [5][5][10];
int rankcount [5][5];

char tempname[2][10];
int tempcount[2];

char username[10];
char inputname[10];
int usercount[5] = {0,0,0,0,0};
int userlevel = 0;



int main()
{
	int level;
	startview();
	//printf("%s",username);
	
	printf(" level을 선택하세요 : ");
	scanf("%d",&level);
	level --;
	printf("usercount 갯수 : ");
	scanf("%d",&usercount[level]);
	levelranking(level);
	rankingsave();
	return 0;
	
}
void levelranking(int level)
{
	int length ;
	//printf("level ranking 함수 시작 \n");
	rankingcompare(level);

	//printf("혹시 여기가?");
	 printf(" map %d\n", level+1);
	 
		for( int j = 0; j<5 ; j++)
		{
			length = 0;
			//for(int k =0; k<5; k++)
			//{

		 printf("%-10s",rankname[level][j]);

			//}
			printf(" %d\n",rankcount[level][j]);
		}


	return ;
}
void rankingcompare(int level)
{
	//printf("rankingcompare시작\n");
	rankingUproad();
	int count = 0;
	//printf("%s : %d\n", userdata[level].name, userdata[level].count);

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
void rankingreset()
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
void rankingsave()
{
	int length;
	//printf("rankingsave함수시작\n");
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

          //fprintf(ranksave,"%s %d\n",rankname[i][j],rankcount[i][j]);
         
		 }
		 fprintf(ranksave, " %d\n",rankcount[i][j]);
		 }
	 }
	 fclose(ranksave);
		return ;

}

void rankingUproad()
{
	//printf("rankinguproad시작\n");
	rankopen = fopen("ranking.txt","rt");
	int ret;
	char tempn[10];
	int tempc;
	//int length;
	
	if ( rankopen == NULL)
	{
//	printf(" rankopen == null\n");
	rankingreset();
	rankingsave();
	}
//	printf("rankopen not null\n");
	rankopen = fopen("ranking.txt","rt");
	while(1)
	{	for(int i = 0 ; i<5 ; i++)
		{for(int j = 0; j<5 ; )
			{
			    //printf("???dddd\n");
				
				ret = fscanf(rankopen,"%s %d",tempn, &tempc);
				if(!(strcmp(tempn,"map")))
				{
					;
				}
				//else if(!(strcmp(tempn,null)))
				//	;
				else
				{
					//printf("else문실행하나?");
					//length =0;
          
					//printf("********i: %d , j : %d tempn : %s , tempc : %d \n",i+1,j+1,tempn, tempc);

					//length = strlen(tempn);
					//printf("length : %d\n",tempn);

					for(int k = 0 ; k<10 ; k++)
					{
						rankname[i][j][k] = tempn[k];
					}
					rankcount[i][j] = tempc;
					j++;
				}
				
				//printf("****level : %d j : %d rankname : %s rankcount %d\n",i+1,j+1,rankname[i][j], rankcount[i][j]);

			}
			if(ret==EOF) break;
		
		}
		if(ret == EOF) break;
	}
	fclose(rankopen);

	return ;
}
void startview()
{
	printf("sokoban\n");
	printf("start .... \n");

	login();
}
void login()
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

void arrayCopy(char dst[], const char src[], int n)
{
	for(int i = 0; i<n; i++)
	{
		dst[i] = src[i];
	}
	return ;
}
