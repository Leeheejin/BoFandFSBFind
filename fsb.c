#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#pragma GCC diagnostic ignored "-Wformat-security"

#define MAX_PAPER 30
#define PAPER_X 10
#define PAPER_Y 10

typedef struct {
	char buf[PAPER_Y][PAPER_X];
}PAPER;

typedef struct {
	PAPER paper[MAX_PAPER];
}SKETCH;

SKETCH sketch;
unsigned int idx=1;

void print_menu()
{
	puts("1. Draw new page");
	puts("2. List page");
	puts("3. List all pages");
	puts("4. Delete page");
	puts("5. Exit");
}

void delete()
{
	int num=0;
	int i=0;
	char is_agree;
	puts("========== WARNING ==========");
	puts("= If you delete paper,      =");
	puts("= you can't recover it.     =");
	puts("= Agree?(y/n)               =");
	puts("=============================");
	fflush(stdin);
	scanf("%1s",&is_agree); // 온전히 'y'의 값만 받아서 판별이 가능하도록 %c 에서 %1s로 바꿉니다.
	while(getchar() != '\n') {getchar();} // 올바른 명령어 입력이 아닌 많은 수의 문자열등이 들어올 경우에 입력을 올바르게 제어하기 위해서 입력 버퍼를 비우도록 허위입력을 받습니다.

	switch(is_agree)
	{
		case 'y':
			printf("select paper number : ");
			fflush(stdout);
			scanf("%1d",&num); // 온전한 값을 입력받기 위해서 입력을 %d %1d로 바꿉니다.
			while(getchar() != '\n') {getchar();} // 올바른 명령어 입력이 아닌 많은 수의 문자열등이 들어올 경우에 입력을 올바르게 제어하기 위해서 입력 버퍼를 비우도록 허위입력을 받습니다.
			if(num < 1 || num > idx)
			{
				printf("You are hacker :( byebye\n");
				exit(0);
			}
			printf("===== sketch %d =====\n",num);
		    for(i=0;i<PAPER_Y;i++)
		    {
		        printf("%s",sketch.paper[num].buf[i]); // 출력 형식을 지정해 FSB를 방지하였습니다. sketch.paper에 들어간 값이 서식 문자로 읽히지 않고 포맷스트링을 지정받아 올바르게 출력될 수 있고 시스템의 안정성을 위협하지 않습니다.
		    }
			printf("======================\n");
			printf("[DELETE] Are you sure?(y/n)");
			scanf("%1s",&is_agree); // 온전히 'y'의 값만 받아서 판별이 가능하도록 %c 에서 %1s로 바꿉니다.
			while(getchar() != '\n') {getchar();} // 올바른 명령어 입력이 아닌 많은 수의 문자열등이 들어올 경우에 입력을 올바르게 제어하기 위해서 입력 버퍼를 비우도록 허위입력을 받습니다.
			if(is_agree == 'y')
			{
				for(int j=0;j<PAPER_Y;j++)
					memset(sketch.paper[num].buf[j],0,PAPER_X);
				printf("Done!\n");
			}
			break;
		case 'n':
			return;
		default:
			puts("type \'y\' or \'n\'");
			return;
		
	}
}

void list_pages()
{
	int i,j;
	for(i=1;i<=idx;i++)
	{
		printf("===== sketch %d =====\n",i);
		for(j=0;j<PAPER_Y;j++)
		{
			printf("%s",sketch.paper[i].buf[j]);
		}
		printf("=====================\n");
	}
}

void list_page()
{
	int i;
	unsigned int num = 0;
	printf("Please input page number to see : ");
	fflush(stdout);
	scanf("%1u",&num); // 입력받을 데이터를 조절해서 하나만 입력할 수 있게 함 %d가 아닌 %u로 변환
	while(getchar() != '\n') {getchar();} // 올바른 명령어 입력이 아닌 많은 수의 문자열등이 들어올 경우에 입력을 올바르게 제어하기 위해서 입력 버퍼를 비우도록 허위입력을 받습니다.

	if(num<1 || num > idx)
	{
		printf("You are hacker :( byebye\n");
		exit(0);
	}

	for(i=0;i<PAPER_Y;i++)
	{
		printf("%s",sketch.paper[num].buf[i]); //출력 형식을 지정해 FSB를 방지하였습니다. sketch.paper에 들어간 값이 서식 문자로 읽히지 않고 포맷스트링을 지정받아 올바르게 출력될 수 있고 시스템의 안정성을 위협하지 않습니다.
	}
}

void draw()
{
	int i,j=0;
	printf("Paper %d\nDraw What you want:)\n",idx);
	for(i=0;i<PAPER_Y;i++)
	{
		read(0,sketch.paper[idx].buf[i],PAPER_X-1); // 입력받을 공간을 저장받을 공간에 지정한 크기 -1 만큼 주어 문자열이 온전히 입력받고 끝에 0x00도 들어갈 수 있게 버퍼 크기를 조절하였습니다.
		//while(getchar() != '\n') {getchar();} // 올바른 명령어 입력이 아닌 많은 수의 문자열등이 들어올 경우에 입력을 올바르게 제어하기 위해서 입력 버퍼를 비우도록 허위입력을 받습니다.
	}
	idx++;
}

int main(int argc, char *argv[], char *envp[])
{
	int choice = 0;

	puts("Dankook Sketchbook");
	while(1)
	{	
		//fflush(stdout);
		choice = 0; // 출력 버퍼로 인해서 choice의 값이 변하는 현상 방지 draw()가 의도치 않게 계속 호출되는 현상 방지
		print_menu();
		scanf("%1d",&choice); // 의도하지 않은 입력을 방지하기 위해서 입력을 %1d로 제한합니다.
		while(getchar() != '\n') {getchar();} // 올바른 명령어 입력이 아닌 많은 수의 문자열등이 들어올 경우에 입력을 올바르게 제어하기 위해서 입력 버퍼를 비우도록 허위입력을 받습니다.
		switch(choice)
		{
			case 1:
				draw();
				break;
			case 2:
				list_page();
				break;
			case 3:
				list_pages();
				break;
			case 4:
				delete();
				break;
			default:
				puts("Thank you for using our sketchbook");
				break;
		}
	}
	return 0;
}
