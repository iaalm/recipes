#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main(int argc,char *argv[])
{
	int sock;
	int addr_len;
	char commond[100]="hello i am ";
	struct sockaddr_in s_addr;
	int len;
	char buff[128];
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket");
		return -1;
	}
	printf("creat socket\n");
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(8081);
	if(argv[1])
		s_addr.sin_addr.s_addr=inet_addr(argv[1]);//input the server ip
	else
	{
		printf("input sever ip\n");
		return -1;
	}
	addr_len=sizeof(s_addr);
	printf("%s\n",commond);
	//strcpy(buff,"hello i am here!");
	strcpy(buff,commond);	
	while(1)
	{
		len=sendto(sock,buff,strlen(buff),0,(struct sockaddr *)&s_addr,addr_len);
		if(len<0)
		{
			printf("rsend error\n\r");
			return -1;
		}
		printf("send success\n\nr");
	}
	return 0;
}
