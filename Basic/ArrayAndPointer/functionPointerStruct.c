#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMD_LENGTH 15
#define NUM_COMMAND 3

/**
函数指针的使用，将函数指针放在结构体里面
输入类似ls -al的命令
**/
void locate(char *args)
{
	char *temp;
	temp=malloc(CMD_LENGTH*sizeof(char));
	strcpy(temp,"locate ");
	strcat(temp,args);
	system(temp);
}

void ls(char *args)
{
	char *temp;
	temp=malloc(CMD_LENGTH*sizeof(char));
	strcpy(temp,"ls ");
	strcat(temp,args);
	system(temp);
}

void netstat(char *args)
{
	char *temp;
	temp=malloc(CMD_LENGTH*sizeof(char));
	strcpy(temp,"netstat ");
	strcat(temp,args);
	system(temp);
}

struct commandStruct
{
	char *commandName;
	void (*commandFunction)(char *args);//函数指针
};

typedef struct commandStruct cs;

//可以看到函数指针的初始化只需要函数的名字即可，不需要写上参数和返回值
static cs commandArray[NUM_COMMAND]={
{"locate",locate},
{"ls",ls},
{"netstat",netstat}
};


int main()
{
	char *input;
	char *args;
	int i=0;
	char c;
	input=malloc(CMD_LENGTH*sizeof(char));
	args=malloc(CMD_LENGTH*sizeof(char));
	printf("请输入您要执行的命令：\n");
	//接收输入的命令
	while((c=getchar())!=' ')
	{
		*(input+i)=c;
		i++;
	}
	i=0;
	//接收输入的命令的参数
	while((c=getchar())!='\n')
	{
		*(args+i)=c;
		i++;
	}
	*(args+i)='\0';
	//匹配命令并执行
	for(i=0;i<NUM_COMMAND;i++)
	{
		if(strcmp(input,commandArray[i].commandName)==0)
		{
			commandArray[i].commandFunction(args);
		}
	}
	
	return 0;
}
