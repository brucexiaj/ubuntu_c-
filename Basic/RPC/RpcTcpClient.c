// RpcTcpClient.cpp : �������̨Ӧ�ó������ڵ㡣
//�ͻ���

#include <stdio.h>

#include <sys/socket.h>

#pragma  comment(lib,"ws2_32.lib")  
  
  

int main(int argc, char* argv[])  
{  
	while(true)
	{
		char *processName;
		char *argument;
		processName = (char *)malloc(40); 
		argument = (char *)malloc(80); 
		printf("��������Ҫ���õĹ�����:\nsayHello(char *name,int age);\nadd(int x,float y);\nprintStudent(int age,char *name,char *sex);\n");
		gets(processName);
		printf("�������������������֮����Ӣ��ð��:����\n");
		gets(argument);

		WORD sockVersion = MAKEWORD(2,2);  
		WSADATA data;   
		if(WSAStartup(sockVersion, &data) != 0)  
		{  
			return 0;  
		}  
  
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
		if(sclient == INVALID_SOCKET)  
		{  
			printf("invalid socket !");  
			return 0;  
		}  
	
		sockaddr_in serAddr;  
		serAddr.sin_family = AF_INET;  
		serAddr.sin_port = htons(10086);  
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");   
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)  
		{  
			printf("connect error !");  
			closesocket(sclient);  
			return 0;  
		}  
		
		char *sendData;
		sendData = (char *)malloc(130); //��仰һ��������
		strcpy (sendData,processName);
		strcat (sendData,"#");
		strcat (sendData,argument);
		send(sclient, sendData, strlen(sendData), 0);  
	
		char recData[255];  
		int ret = recv(sclient, recData, 255, 0);  
		if(ret > 0)  
		{  
			recData[ret] = 0x00;  
			printf("�������˷��صĽ���ǣ�\n");
			printf(recData);  
			printf("\n");
			printf("\n");
		}

	}

	
    //closesocket(sclient);  
    WSACleanup();  
    return 0;  
}  

