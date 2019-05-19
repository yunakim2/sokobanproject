void PrintMoveAction()
{
	int dx, dy;
	char ch;

	ch=getchar();
	
	if(ch==e)
	{
		exit(0);
	}
	else if(ch == 'r'||ch =='R')
	{
		Re();
	}

	else if(ch==-32)
	{
		ch=getchar();
		switch(ch)
		{
			case h:
				dx = -1; dy = 0; break;
			case j:
				dx = 0; dy = 1; break;
			case k:
				dx = 0; dy = -1; break;
			case l: dx = 1; dy = 0; break;
		}
		if (stage[Roundy+dy][Roundx+dx] == '#')
		{
			return;
		}
		Roundx += dx;
		Roundy += dy;
		NumMove ++;
	}
}

/* gotoxy*/
void gotoxy(int x, int y){
	printf("\033[%d;%df",y,x);
	fflush(stdout);
}
void PrintInfo()//int NumMove필요
{
	gotoxy(59,2); printf(" S O K O B A N");

	gotoxy(61,5); printf("스테이지 : %d", MAXSTAGE - 1);
	gotoxy(61,7); printf("움직인 횟수 : %d", NumMove);

	gotoxy(67,10); printf("UP");
	gotoxy(67,11); printf("k");
	gotoxy(60,12); printf("LEFT h l RIGHT");
	gotoxy(67,13); printf("j");
	gotoxy(66,14); printf("DOWN");

	gotoxy(61,16); printf("다시하기 : R");
}

