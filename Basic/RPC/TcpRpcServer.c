// TcpRpcServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>  
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")  
  

//sayHello����
char *sayHello(char *myName,int myAge)
{
	
	char stringAge[4];
	itoa(myAge, stringAge, 10);
	char *result;
	result = (char *)malloc(60); //��仰һ��������
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

/* ����ָ�� */
typedef char* (*process)(char *a);

typedef struct mydata 
{
    process fcb; /* ���������� */
	char *processName;
} mydata_t;

/* ����ʱ������Ӧ�ĺ��������� */
//������ע��
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
//����ṹ���Լ���ʽ����Ϊ�ṹ��ĺ���
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
	result = (char *)malloc(80); //��仰һ��������
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
	//��ʼ��ע���
	mydata_t *myProcess[100];
	for(int i=0;i<100;i++)
	{
		myProcess[i]=NULL;
	}
	//ע�ắ��
	
	myProcess[0]=mydata_create(preSayHello,"sayHello"); 
    
	myProcess[1]= mydata_create(preAdd,"add");
	myProcess[2]= mydata_create(prePrintStudent,"printStudent");
	
	char *processName;
	char *argument;
	
	
	

    //��ʼ��WSA  
    WORD sockVersion = MAKEWORD(2,2);  
    WSADATA wsaData;  
    if(WSAStartup(sockVersion, &wsaData)!=0)  
    {  
        return 0;  
    }  
  
    //�����׽���  
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(slisten == INVALID_SOCKET)  
    {  
        printf("socket error !");  
        return 0;  
    }  
  
    //��IP�Ͷ˿�  
    sockaddr_in sin;  
    sin.sin_family = AF_INET;  
    sin.sin_port = htons(10086);  
    sin.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)  
    {  
        printf("bind error !");  
    }  
  
    //��ʼ����  
    if(listen(slisten, 5) == SOCKET_ERROR)  
    {  
        printf("listen error !");  
        return 0;  
    }  
  
    //ѭ����������  
    SOCKET sClient;  
    sockaddr_in remoteAddr;  
    int nAddrlen = sizeof(remoteAddr);  
    char revData[255];   
    while (true)  
    {  
        printf("�ȴ�����...\n");  
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);  
        if(sClient == INVALID_SOCKET)  
        {  
            printf("accept error !");  
            continue;  
        }  
        printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));  
          
        //��������  
        int ret = recv(sClient, revData, 255, 0);          
        if(ret > 0)  
        {  
			//���տͻ��˵����ݣ������������������
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
		//���ݺ�������������Ӧ�ĺ���������������Ľ��
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
			
        //���ͺ������õĽ��  
        //char * sendData = "��ã�TCP�ͻ��ˣ�\n";  
        send(sClient, sendData, strlen(sendData), 0);  
        //closesocket(sClient);  
    }  
     closesocket(sClient);  
      
    closesocket(slisten);  
    WSACleanup();  
    return 0;  
}  

