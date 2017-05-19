#include <stdio.h>

//普通的交换函数，无法实现交换
void swap(int x,int y)
{
   int temp=x;
    x=y;
    y=temp;
}


//形式参数是指针的交换函数可以实现交换
void swap_pointer(int *x,int *y)
{
   int temp=*x;
    *x=*y;
    *y=temp;
}

//形式参数是字符串指针，不能改变原来的字符串
void stringPointer(char *s)
{
    s="changed";
}

//统计字符串长度
int myLength(char *s)
{
    int length=0;
    for(;*s!='\0';*s++)
    length++;
    return length;
}
    
int main()
{
    int a[7]={1,2,3,4,5,6,7};
    //1.数组的名字表示数组的第一个元素的地址
    int *p=a;//等价与int *p=&a[0];
    printf("%d\n",*p);
    //2.指针每加1,表示向后移动sizeof(数组元素类型)
    printf("%d\n",*(p+1));
    //3.直接用数组名表示数组第一个元素
    printf("%d\n",*a);
    //4.但是下面这条语句就不可以
    //printf("%d\n",&a);
    //5.数组名字也可以直接加1,表示后面的地址
    printf("%d\n",*(a+1));

    //6.函数不能改变实际参数的值
    int x=1,y=2;
    swap(x,y);
    printf("x:%d;y:%d\n",x,y);
    //7.形式参数是指针才能改变实际参数的值
    swap_pointer(&x,&y);
    printf("x:%d;y:%d\n",x,y);

    //8.通过指针改变值
    int z=1;
    int *pz=&z;
    *pz=11;
    printf("z的当前值:%d\n",z);

    //9.形式参数是字符串指针时，改变形式参数并不会改变实际参数的值，这里要特别与7区分
    char *b="notchange";
    stringPointer(b);
    printf("调用了函数后的字符串a:%s\n",b);//这里打印的是b，不是*b，一定要注意
    //10.统计字符串长度
    printf("notchange的长度是:%d\n",myLength(b));

    //11.指针数组在字符串中的应用
    char *pointerArrayString[]={"Monday","Tuesday","Wendesday","Thursday","Friday","Saturday","Sunday"};
    printf("第一个字符串是:%s\n",*pointerArrayString);
    printf("第一个字符串的第一个字符是:%c\n",*pointerArrayString[0]);

    return 0;
}
