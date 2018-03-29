/*
	homework 1 : BoF
	This program has several BoF vulnerabilities.
	Find and fix them.
	You can do anything(change functions, include extra headers, ...) to fix this program,
	but it MUST work properly.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXBUF 256

struct info
{
	char name[16];
	char phone[16];
	char address[MAXBUF];
} __attribute__((packed));
typedef struct info INFO;

unsigned int is_license_agree;

void print_menu()
{
	fflush(stdout);
	puts("1. License Agreement");
	puts("2. Register Name");
	puts("3. Register Phone Number");
	puts("4. Register Address");
	puts("5. Print Information");
	puts("6. Exit");
}

unsigned int get_choice()
{
	unsigned int i=0;
	printf(">>>");
	fflush(stdout);
	scanf("%u",&i);
	//fflush(stdin);
	while(getchar() != '\n') {getchar();}
	return i;
}
// i 값에 부호가 없는 정수를 제외한 값이 들어가는 경우(문자열 등)에 대해 원래 프로그래머가 의도하지 않은 실행이 발생할 수 있습니다.
// fflush는 리눅스에서는 출력버퍼를 비우는 함수이기 때문에 입력버퍼를 비우려는 목적에 제대로 작동하지 않아서 주석처리하였습니다.
// 대신, 매 입력마다 getchar() 를 사용하여 입력 버퍼를 비워 의도치 않은 실행을 방지합니다.
int chk_license()
{
	if(is_license_agree != 1)
	{
		puts("You must accept the license first");
		is_license_agree = 0;
		return -1;
	}
	else
		return 0;
}

void license()
{
	char buf[4]; //yes 와 no로 정확한 입력을 받기 위하여 buf 공간을 16에서 4로 수정합니다.
	memset(buf,0,3); // 마찬가지로 초기화도 buf 공간의 16까지가 아닌 4까지 초기화합니다.

	if(is_license_agree == 1)
	{
		puts("You already agree");
		return;
	}

	system("clear");
	puts("########################################");
	puts("#           Dankook License            #");
	puts("########################################");
	puts("# I will not cheat this homework.      #");
	puts("# I will not sleep in class.           #");
	puts("# I will do my best.                   #");
	puts("########################################");
	printf("Do you agree\?\?(yes/no)");
	fflush(stdout);
	fgets(buf,sizeof(buf)-1,stdin); // 256에서 sizeof(buf)-1 으로 입력받을 공간을 제한합니다.
	
	if(sizeof(buf) > 4) // 입력이 제대로 들어왔다면 버퍼를 비우기 위해서 \n을 한번 더 입력하지 않아도 됩니다.
		while(getchar() != '\n') {getchar();}
		// 입력버퍼를 완전히 비울때까지 반복합니다.

	if(buf[0] == 'Y' || buf[0] == 'y')
	{
		puts("Thank you for agreement!");
		is_license_agree = 1;
	}
	else
	{
		is_license_agree = 0;
	}
}

void reg_name(INFO *myinfo)
{
	if(!chk_license())
	{
		system("clear");
		puts("What is your name?");
		printf(">>> ");
		fflush(stdout);
		getchar();
		scanf("%s",myinfo->name);
		printf("Hello %s\n",myinfo->name);
	}
}

void reg_phone(INFO *myinfo)
{
	char buf[16];
	memset(buf,0,16);
	if(!chk_license())
	{
		system("clear");
		puts("What is your phone number?");
		printf(">>> ");
		fflush(stdout);
		getchar();
		fgets(buf,15,stdin); // 전화번호를 받을 공간을 256에서 최대 15까지 받을 수 있게 제한하는 것으로 수정합니다.
		buf[strlen(buf)-1] = '\x00';
		strncpy(myinfo->phone,buf,15);
		puts("Phone number Registration Complete!");
		
		while(getchar() != '\n') {getchar();}
		// 입력버퍼를 완전히 비울때까지 반복합니다.
	}
}

void reg_address(INFO *myinfo)
{
	if(!chk_license())
	{
		system("clear");
		puts("What is your address?");
		printf(">>> ");
		fflush(stdout);
		getchar();
		read(0,myinfo->address,MAXBUF);
		puts("Address Registration Complete!");
	}
}

void print_info(INFO *myinfo)
{
	if(!chk_license())
	{
		printf("name : %s\n",myinfo->name);
		printf("phone number : %s\n",myinfo->phone);
		printf("address : %s\n",myinfo->address);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	INFO myinfo;
	unsigned int choice=0;
	memset(&myinfo,0,sizeof(INFO));

	puts("#######Simple MyInfo Service#######");
	while(1)
	{
		print_menu();
		choice = get_choice();
		switch(choice)
		{
			case 1:
				license();
				break;
			case 2:
				reg_name(&myinfo);
				break;
			case 3:
				reg_phone(&myinfo);
				break;
			case 4:
				reg_address(&myinfo);
				break;
			case 5:
				print_info(&myinfo);
				break;
			case 6:
				puts("Thank you for using MyInfo Service");
				return 0;
			default:
				puts("No menu");
				break;
		}
	}
	return 0;
}
