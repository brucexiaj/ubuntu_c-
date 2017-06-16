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

int main()
{
    //定义sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    
    //定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip

    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

   
  
   
    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    char buff[120];

    printf("请输入过程名#参数1:参数2:参数3。。。\n");
    printf("例如：sayHello#Tom:22\n");
    while (fgets(sendbuf,sizeof(char)*120, stdin) != NULL)
    {
        char *buffPointer=sendbuf;
	XDR xdr;
  

        xdrmem_create(&xdr,buff,120,XDR_ENCODE);
        xdr_string(&xdr,&buffPointer,sizeof(char)*120);
      
        send(sock_cli, buff, sizeof(char)*120,0); ///发送
    
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
        char buff1[120];
        char *pp=buff1;
        XDR xdr1;
  

        xdrmem_create(&xdr1,recvbuf,120,XDR_DECODE);
        xdr_string(&xdr1,&pp,sizeof(char)*120);
        printf("结果：%s\n",pp);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
        printf("请输入过程名#参数1:参数2:参数3。。。\n");
        printf("例如：sayHello#Tom:22\n");
    }

    close(sock_cli);

    return 0;
}
