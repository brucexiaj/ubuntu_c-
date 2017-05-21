#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXROW 10
#define MAXLENGTH 10
/**
键盘输入10行英文字母，每行字母最大长度为10，
先在行内排序，即按照a-z的顺序排序
然后在行与行之间排序，按每一行的首字母排序
**/

int main()
{
	char *input[MAXROW];
	//Input text to be sorted from the keyboard
	printf("please input %d line text\n",MAXROW);
	int j=0,i=0;
	for(i=0;i<MAXROW;i++)
	{
		input[i]=malloc(MAXROW*(sizeof(char)));
		for(j=0;j<MAXLENGTH;j++)
		{
			scanf("%c",input[i]+j);
			if(*(input[i]+j)=='\n')
			break;
		}
		*(input[i]+j)='\0';
	}

	//Sort every line according to the sequence of every character
	for(int k=0;k<MAXROW;k++)
	{
		int length=0;
		//get the length of temporary
		for(i=0;i<MAXLENGTH;i++)
		{
			if(*(input[k]+i)=='\0')
			{
				break;
			}
			length++;
		}
		for(i=0;i<length;i++)
		{
			for(j=i+1;j<length;j++)
			{
				char first=*(input[k]+i);
				char second=*(input[k]+j);
				if(first>second)
				{
					char temp=*(input[k]+i);
					*(input[k]+i)=*(input[k]+j);
					*(input[k]+j)=temp;
				}	
			}
		}
	}

	//Sort the text according to the first charactre of every line
	for(i=0;i<MAXROW;i++)
	{
		for(j=i+1;j<MAXROW;j++)
		{
			char first=*input[i];
			char second=*input[j];
			if(first>second)
			{
				char *temp=input[i];
				input[i]=input[j];
				input[j]=temp;
			}
		}
	}

	//print the result on the screen
	printf("Result:\n");
	for(i=0;i<MAXROW;i++)
	{
		
		printf("%s\n",input[i]);
		
	}

	//store the result in disk
	FILE *filePointer;
	if((filePointer=fopen("stringSortResult","w"))==NULL)
	{
		system("touch stringSortResult");
		filePointer=fopen("stringSortResult","w");
	}
	for(i=0;i<MAXROW;i++)
	{
		
		fputs(input[i],filePointer);
		putc('\n',filePointer);
	}
	fclose(filePointer);
	return 0;
}
