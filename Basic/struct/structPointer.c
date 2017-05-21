#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORDS 10
#define WORDLENGTH 15
#define STRUCT_LENGTH 5
/**
从键盘输入10个单词，每个单词的最大长度15,单词之间以回车键隔开
单词必须是keytab数组中的单词
统计每个单词的出现次数，将结果存入磁盘中
**/
struct key
{
	char *word;
	int count;
};

typedef struct key keyStruct;
keyStruct keytab[STRUCT_LENGTH]={{"auto",0},{"char",0},{"const",0},{"int",0},{"void",0}};



void binsearch(char *input[],keyStruct *keytab)
{
	for(int i=0;i<MAXWORDS;i++)
	{
		int start=0;
		int end=STRUCT_LENGTH-1;
		while(start<=end)
		{
			//printf("%d,%d\n",start,end);
			int middle=(start+end)/2;
			struct key *temp=&keytab[middle];
			if(strcmp(input[i],temp->word)<0)
			{
				end=middle-1;
			}
			else if(strcmp(input[i],temp->word)>0)
			{
				start=middle+1;
			}
			else
			{
				temp->count++;
				break;
			}
			
		}
	}
}

int main()
{
	//接受从键盘的输入并存入字符串指针数组中
	char *input[MAXWORDS];
	printf("Please input the key word in C language.\n");
	int i=0,j=0;
	for(i=0;i<MAXWORDS;i++)
	{
		input[i]=malloc(WORDLENGTH*(sizeof(char)));
		for(j=0;j<WORDLENGTH;j++)
		{
			
			if((*(input[i]+j)=getchar())=='\n')
			break;
		}
		*(input[i]+j)='\0';
		//printf("ceshi\n");
		
	}
	
	//统计字符串出现的次数，存入keytab中
	binsearch(input,keytab);

	//打印统计的结果
	for(i=0;i<STRUCT_LENGTH;i++)
	{
		printf("%s:%d\n",keytab[i].word,keytab[i].count);
	}

	//将结果存入磁盘的文件中
	FILE *file;
	if((file=fopen("structPointerResult","w"))==NULL)
	{	
		system("touch structPointerResult");
		file=fopen("structPointerResult","w");
	}
	for(i=0;i<STRUCT_LENGTH;i++)
	{
		fputs(keytab[i].word,file);
		putc(':',file);
		fprintf(file,"%d",keytab[i].count);
		putc('\n',file);
	}
	fclose(file);	
	return 0;
}
