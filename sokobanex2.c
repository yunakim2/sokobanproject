
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

char inputname[MAX_NAME_LENGTH];
FILE *save;
FILE *rankopen;
FILE *ranksave;

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
	inputkeybord();
	return ;
}
void inputkeybord()
{
	char c;
	while(1)
	{ c = getchar();
	  getchar();
	 switch(c)
		{
			case 'h' :
				break;
			case 'j' :
				break;
			case 'k' :
				break; 
			case 'l' :
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
	char ch ;
	rankopen = fopen("ranking.txt","r");
	if(rankopen == NULL)
	{
		printf("rankng 파일 열기 실패 ! \n");
		return;
	}
	while(1)
	{
		ch = fgetc(rankopen);
		if(ch ==EOF)
			break;
		putchar(ch);
	}
	fclose(rankopen);

	return ;
}
void rankingsave()
{
	ranksave = fopen("ranking.txt","w");
	rankingcompare();
	fprintf(ranksave,"ranking 저장 파일 입니다.\n");
	fclose(ranksave);
	printf("raking 파일이 저장되었습니다.\n");
	return ;

}

void rankingcompare()
{
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
	fclose(save);
	rankingsave();
	printf("소코반 파일이 저장되었습니다.\n");

	return ;
}

