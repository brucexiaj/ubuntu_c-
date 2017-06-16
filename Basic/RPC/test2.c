#include <stdio.h>  
#include <rpc/rpc.h>  
int main()  
{  
    printf("begin\n");  
  
    FILE * pFile = fopen("lww.txt","rb");  
    XDR  XDR;  
    xdrstdio_create(&XDR,pFile,XDR_DECODE);  
    int n = 0;  
    xdr_int(&XDR,&n);  
    xdr_destroy(&XDR);  
    fclose(pFile);  
  
    printf("%d\n",n);  
  
    printf("end\n");  
  
    return 0;  
} 
