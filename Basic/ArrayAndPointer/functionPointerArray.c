#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMD_LENGTH 15

void date()
{
	system("date");
}

void ls()
{
	system("ls -al");
}

void ifconfig()
{
	system("ifconfig");
}

int main()
{
	int input;
	
	printf("请输入您要执行的命令的序号：\n");
	scanf("%d",&input);
	//printf("%s",input);
	//函数指针组成的数组
	void (*command[])(void)={date,ls,ifconfig};
	printf("以下是执行结果：\n");
	command[input]();
	return 0;
}
