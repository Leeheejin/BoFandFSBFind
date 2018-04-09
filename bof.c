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
	while(i > 4294967295) {
		printf("올바른 값을 입력해 주십시오\n");
		printf(">>>");
		scanf("%u",&i);
	}
	//fflush(stdin);
	while(getchar() != '\n') {getchar();}
	return i;
}
// i 값에 부호가 없는 정수를 제외한 값이 들어가는 경우(문자열 등)에 대해 원래 프로그래머가 의도하지 않은 실행이 발생할 수 있습니다.
// fflush는 리눅스에서는 출력버퍼를 비우는 함수이기 때문에 입력버퍼를 비우려는 목적에 제대로 작동하지 않아서 주석처리하였습니다.
// 대신, 매 입력마다 getchar() 를 사용하여 입력 버퍼를 비워 의도치 않은 실행을 방지합니다.
// i 의 값엔 의 i값을 넘어가는 값이 들어갈 수 있습니다. 그러나 main함수에서 switch를 통해 값을 제어하고 있으므로 쓰레기 값이 넘어가게 되더라도 정상적인 실행이 가능합니다.
// 그렇지만 프로그래머의 의도 (올바른 명령어를 사용하게 끔 유도)에 맞게 i의 입력최댓값을 제어하였습니다.

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
	memset(buf,0,sizeof(buf)); // 마찬가지로 초기화도 buf 공간의 16까지가 아닌 4까지 초기화합니다.

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
	fgets(buf,sizeof(buf)-1,stdin); // 입력받을 공간 크기를 256에서 sizeof(buf)-1 으로 제한합니다.
	
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
		scanf("%15s",myinfo->name); // 변환명세 변경을 통해 입력 최대 길이를 제한하여 버퍼오버플로우를 막습니다. %s -> %16s
		printf("Hello %s\n",myinfo->name);
	}
}
//입력 사이에 공백이 있을 경우 제대로 값을 받아들이지 못하고 버퍼오버플로우가 발생하여 phone number를 담을 공간과 address를 저장할 공간을 침범합니다.

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
		fgets(buf,sizeof(buf) - 1,stdin); // 전화번호를 받을 공간을 256에서 buf 배열의 크기보다 하나 작은만큼 입력을 받게 15로 제한하는 것으로 수정합니다. 16이 아닌 이유는 string의 끝 부분을 알아야 해서 \n이 들어갈 공간을 남겼습니다.
		buf[strlen(buf)] = '\x00'; //strlen(buf)-1 에서 수정하였습니다.
		strncpy(myinfo->phone,buf,16);
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
		read(0,myinfo->address,MAXBUF-1);
		// MAXBUF만큼의 데이터가 들어오는 것을 테스트하여 입력한 데이터가 손상하는 것을 발견하였습니다. 이에,
		// 입력받을 공간의 크기를 MAXBUF의 크기보다 1바이트 작은 공간으로 할당하여 문자열의 끝을 알 수 있게 하였습니다. 
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
