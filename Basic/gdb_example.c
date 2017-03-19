#include <stdio.h>
int cnt=0;
void my_print();
void main()
{
	int i,j;
	for(i=1;i<=5;i++)
	{
		for(j=1;j<=5;j++)
		{
			my_print(i,j);
		}
	}
}

void my_print(int a,int b)
{	
	cnt++;
	printf("本次操作内层循环为%d,外层循环为%d,总次数为%d",a,b,cnt);
}
	
