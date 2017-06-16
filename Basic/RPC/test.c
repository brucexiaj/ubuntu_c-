    #include <stdio.h>  
    #include <rpc/rpc.h>  
//encode
    int main()  
    {  
/**
        printf("begin\n");  
      
        FILE * pFile = fopen("lww.txt","ab+");  
        XDR  XDR;  
        xdrstdio_create(&XDR,pFile,XDR_ENCODE);  
        int n = 200;  
        xdr_int(&XDR,&n);  
        xdr_destroy(&XDR);  
        fclose(pFile);  
      
        printf("xdr_destroy \n");  
**/
    
    char name[20];
    strcpy(name,"LJ");
    char *p = name;

 char args[100]="xi:22.4:xj";
    //strcpy(args,"xi:22:jun");
    char *p1 = args;

int age=23;

    XDR xdr;
    char buff[120];

    xdrmem_create(&xdr,buff,120,XDR_ENCODE);
	xdr_string(&xdr,&p,sizeof p);
xdr_string(&xdr,&p1,sizeof(char)*100);
//xdr_int(&xdr,&age);

 XDR xdr1;
xdrmem_create(&xdr1,buff,120,XDR_DECODE);

    char name1[20];
    char *p2 = name1;
 xdr_string(&xdr1,&p2,sizeof p2);
    printf("name:%s\n",p2);

char args2[100];
    char *p3 = args2;
 xdr_string(&xdr1,&p3,sizeof(char)*100);
    printf("args:%s\n",p3);

 //int age2;
    //xdr_int(&xdr,&age2);
//printf("age:%d\n",age2);

        return 0;  
    }  
