// TcpRpcServer.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>  
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")  
  

//sayHello函数
char *sayHello(char *myName,int myAge)
{
	
	char stringAge[4];
	itoa(myAge, stringAge, 10);
	char *result;
	result = (char *)malloc(60); //这句话一定不能少
    strcpy (result,"Hello, ");
    strcat (result,stringAge);
    strcat (result," years old ");
    strcat (result,myName);
	
    return result;
}
char *preSayHello(char *argument)
{
	char *arguments1;
	int arguments2;
	int count=0;
	char* token = strtok( argument, ":");
	while( token != NULL )
	{
		switch(count)
		{
			case 0:arguments1=token;break;
			case 1:arguments2=atoi(token);break;
			default:break;
		}
		count++;
		token = strtok( NULL, ":");
	}
	return sayHello(arguments1,arguments2);
}

/* 函数指针 */
typedef char* (*process)(char *a);

typedef struct mydata 
{
    process fcb; /* 函数管理器 */
	char *processName;
} mydata_t;

/* 创建时传入相应的函数管理器 */
//函数的注册
mydata_t* mydata_create(process out_fcb,char *processName)
{
    mydata_t *data = (mydata_t *)malloc(sizeof(mydata_t));
    data->fcb = out_fcb;
	data->processName=processName;
    return data;
}

float add(int x,float y)
{
	float z;
	z=x+y;
	return z;
}
char *preAdd(char *argument)
{
	int arguments1;
	float arguments2;
	int count=0;
	char* token = strtok( argument, ":");
	while( token != NULL )
	{
		switch(count)
		{
			case 0:arguments1=atoi(token);break;
			case 1:arguments2=atof(token);break;
			default:break;
			
		}
		count++;
		token = strtok( NULL, ":");
	}
	char *stringResult; 
	stringResult = (char *)malloc(30);
	float z=add(arguments1,arguments2);
	sprintf(stringResult,"%f",z);
	return stringResult;
}
//定义结构体以及形式参数为结构体的函数
typedef struct
{
	int age;
	char *name;
	char *sex;
}Student;

char  *printStudent(Student *student)
{
	//printf("name:%s,age:%d\n",student->name,student->age);
	char stringAge[5];
	itoa(student->age, stringAge, 10);
	char *result;
	result = (char *)malloc(80); //这句话一定不能少
    strcpy (result,"name:");
	strcat (result,student->name);
    strcat (result,"age:");
    strcat (result,stringAge);
	strcat (result,"sex:");
	strcat (result,student->sex);
    return result;
}

char *prePrintStudent(char *argument)
{
	int arguments1;
	char *arguments2;
	char *arguments3;
	int count=0;
	char* token = strtok( argument, ":");
	while( token != NULL )
	{
		switch(count)
		{
			case 0:arguments1=atoi(token);break;
			case 1:arguments2=token;break;
			case 2:arguments3=token;break;
			default:break;
			
		}
		count++;
		token = strtok( NULL, ":");
	}
	Student *student;
	student=(Student *)malloc(sizeof(Student));
	student->age=arguments1;
	student->name=arguments2;
	student->sex=arguments3;
	char *stringResult; 
	stringResult=printStudent(student);
	return stringResult;
}

int main(int argc, char* argv[])  
{  
	//初始化注册表
	mydata_t *myProcess[100];
	for(int i=0;i<100;i++)
	{
		myProcess[i]=NULL;
	}
	//注册函数
	
	myProcess[0]=mydata_create(preSayHello,"sayHello"); 
    
	myProcess[1]= mydata_create(preAdd,"add");
	myProcess[2]= mydata_create(prePrintStudent,"printStudent");
	
	char *processName;
	char *argument;
	
	
	

    //初始化WSA  
    WORD sockVersion = MAKEWORD(2,2);  
    WSADATA wsaData;  
    if(WSAStartup(sockVersion, &wsaData)!=0)  
    {  
        return 0;  
    }  
  
    //创建套接字  
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(slisten == INVALID_SOCKET)  
    {  
        printf("socket error !");  
        return 0;  
    }  
  
    //绑定IP和端口  
    sockaddr_in sin;  
    sin.sin_family = AF_INET;  
    sin.sin_port = htons(10086);  
    sin.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)  
    {  
        printf("bind error !");  
    }  
  
    //开始监听  
    if(listen(slisten, 5) == SOCKET_ERROR)  
    {  
        printf("listen error !");  
        return 0;  
    }  
  
    //循环接收数据  
    SOCKET sClient;  
    sockaddr_in remoteAddr;  
    int nAddrlen = sizeof(remoteAddr);  
    char revData[255];   
    while (true)  
    {  
        printf("等待连接...\n");  
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);  
        if(sClient == INVALID_SOCKET)  
        {  
            printf("accept error !");  
            continue;  
        }  
        printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));  
          
        //接收数据  
        int ret = recv(sClient, revData, 255, 0);          
        if(ret > 0)  
        {  
			//接收客户端的数据，并分离出函数名参数
            revData[ret] = 0x00;  
            printf("revData:%s\n",revData);
			int count=0;
			char* token = strtok( revData, "#");

			while( token != NULL )
			{
				switch(count)
				{
				case 0:processName=token;break;
				case 1:argument=token;break;
				default:break;
				}
				count++;
				token = strtok( NULL, "#");
            }
        } 
		char *sendData;
		//根据函数名，调用相应的函数，并输出函数的结果
		for(int i=0;i<100;i++)
		{
			if(myProcess[i]!=NULL)
			{
				char *currentProcessName=myProcess[i]->processName;
				if(strcmp(currentProcessName,processName)==0)
				{
					
					sendData=myProcess[i]->fcb(argument);
					printf("sendData:%s\n",sendData);
					break;
				}
			}
		}
			
        //发送函数调用的结果  
        //char * sendData = "你好，TCP客户端！\n";  
        send(sClient, sendData, strlen(sendData), 0);  
        //closesocket(sClient);  
    }  
     closesocket(sClient);  
      
    closesocket(slisten);  
    WSACleanup();  
    return 0;  
}  

