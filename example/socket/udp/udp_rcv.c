#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main()
{
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	int sock;
	socklen_t addr_len;
	int len;
	char buff[320*240];
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket\n");
		return -1;
	}
	printf("creat socket\n");
	memset(&s_addr,0,sizeof(struct sockaddr_in));
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(8081);	
	s_addr.sin_addr.s_addr=INADDR_ANY;//本地的任意ip信息
	if((bind(sock,(struct sockaddr *)&s_addr,sizeof(s_addr)))==-1)
	{
		perror("bind");
		return -1;
	}
	printf("bind success\n");
	addr_len=sizeof(c_addr);
	while(1)
	{
		printf("========\n");
		len=recvfrom(sock,buff,sizeof(buff)-1,0,(struct sockaddr *)&c_addr,&addr_len);
		if(len<0)
		{
			perror("recvfrom");
			return -1;
		}
		buff[len]='\0';
		printf("recive come from %s :%d message:%s\n\r",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port),buff);
	}
	return 0;
}
