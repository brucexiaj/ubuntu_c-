#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <rpc/rpc.h> 


#define MYPORT  12318

#define BUFFER_SIZE 120
#define QUEUE 20

//sayHello函数
char *sayHello(char *myName,int myAge)
{
	
	char stringAge[4];
	
        sprintf(stringAge,"%d",myAge);
	char *result;
	result = (char *)malloc(60);
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

//函数指针
typedef char* (*process)(char *a);

//函数指针和函数名字组成的结构体
typedef struct mydata 
{
    process fcb; 
    char *processName;
} mydata_t;

//函数注册
mydata_t* mydata_create(process out_fcb,char *processName)
{
    mydata_t *data = (mydata_t *)malloc(sizeof(mydata_t));
    data->fcb = out_fcb;
    data->processName=processName;
    return data;
}

//add函数
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

//学生结构体
typedef struct
{
	int age;
	char *name;
	char *sex;
}Student;

//打印学生结构体
char  *printStudent(Student *student)
{
	
	char stringAge[5];
	
	sprintf(stringAge,"%d",student->age);
	char *result;
	result = (char *)malloc(80); 
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



int main()
{


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



    	///定义sockfd
    	int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
    	
    	///定义sockaddr_in
    	struct sockaddr_in server_sockaddr;
    	server_sockaddr.sin_family = AF_INET;
    	server_sockaddr.sin_port = htons(MYPORT);
    	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    	///bind，成功返回0，出错返回-1
   	if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    	{
    	    perror("bind");
      	    exit(1);
  	}
	
    	///listen，成功返回0，出错返回-1
    	if(listen(server_sockfd,QUEUE) == -1)
    	{
        	perror("listen");
        	exit(1);
   	 }

    	///客户端套接字
    	char buffer[BUFFER_SIZE];
    	struct sockaddr_in client_addr;
    	socklen_t length = sizeof(client_addr);

    	///成功返回非负描述字，出错返回-1
    	int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    	if(conn<0)
    	{
        	perror("connect");
        	exit(1);
    	}


        //监听
 	while(1)
    	{
        	memset(buffer,0,sizeof(buffer));
		//获取客户的数据
        	int len = recv(conn, buffer, sizeof(buffer),0);
       		//对客户端数据解码
 		XDR xdr1;
       

        	xdrmem_create(&xdr1,buffer,120,XDR_DECODE);
		char rece[120];
        	char *namePointer = rece;
        	xdr_string(&xdr1,&namePointer,sizeof(char)*120);
        	printf("客户端数据:%s\n",namePointer);




		int count=0;
		char* token = strtok( namePointer, "#");
		//分离出函数名和参数
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
        
		char *sendData;
		//通过函数名匹配函数指针，调用函数给出结果
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
	
	//对结果进行XDR 编码后返回给客户端
	char buffer1[120];
 	XDR xdr;
     	xdrmem_create(&xdr,buffer1,120,XDR_ENCODE);   
 	xdr_string(&xdr,&sendData,sizeof(char)*120);
        send(conn, buffer1, len, 0);
    	}
    
    close(conn);
    close(server_sockfd);

   
    return 0;
}
