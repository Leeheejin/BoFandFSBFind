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
	getchar();
	scanf("%c",&is_agree);

	switch(is_agree)
	{
		case 'y':
			printf("select paper number : ");
			fflush(stdout);
			scanf("%d",&num);
			if(num < 1 || num > idx)
			{
				printf("You are hacker :( byebye\n");
				exit(0);
			}
			printf("===== sketch %d =====\n",num);
		    for(i=0;i<PAPER_Y;i++)
		    {
		        printf(sketch.paper[num].buf[i]);
		    }
			printf("======================\n");
			printf("[DELETE] Are you sure?(y/n)");
			fflush(stdin);
			getchar();
			scanf("%c",&is_agree);
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
	scanf("%d",&num);

	if(num<1 || num > idx)
	{
		printf("You are hacker :( byebye\n");
		exit(0);
	}

	for(i=0;i<PAPER_Y;i++)
	{
		printf(sketch.paper[num].buf[i]);
	}
}

void draw()
{
	int i,j=0;
	printf("Paper %d\nDraw What you want:)\n",idx);
	for(i=0;i<PAPER_Y;i++)
	{
		read(0,sketch.paper[idx].buf[i],PAPER_X);
	}
	idx++;
}

int main(int argc, char *argv[], char *envp[])
{
	int choice = 0;

	puts("Dankook Sketchbook");
	while(1)
	{
		print_menu();
		scanf("%1d",&choice); // 의도하지 않은 입력을 방지하기 위해서 입력을 %1d로 제한합니다.
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
