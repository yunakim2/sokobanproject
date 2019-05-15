
#include <stdio.h>
#include <string.h>

void login();
void startview();

#define MAX_NAME_LENGTH 10

char inputname[MAX_NAME_LENGTH];

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
