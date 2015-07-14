#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PORT 12580
#define MAX_BUFFER 1024

int main()
{
	int sockfd,newsockfd,nbyte;
	char buffer[MAX_BUFFER];
	struct sockaddr_in addr;
	int addr_len = sizeof(struct sockaddr_in);
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket created error!");
		exit(1);
	}
	else
	{
		printf("socket created sucessfully!\n");
		printf("socket id:%d\n",sockfd);
	}bzero(&addr,sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr *)(&addr),sizeof(struct sockaddr)) < 0)
	{
		perror("bind error!");
		exit(1);
	}
	else
	{
		printf("bind port successfully!\n");
		printf("local port:%d\n",PORT);
	}
	if(listen(sockfd,5) < 0)
	{
		perror("listen error!");
		exit(1);
	}
	else
	{
		printf("listenning...........\n");
	}
	if((newsockfd = accept(sockfd,(struct sockaddr *)(&addr),&addr_len)) < 0)
	{
		perror("accept error!");
	}
	else
	{
		printf("acceptd a new connecttiom.\n");
		printf("new socket id:%d\n",newsockfd);
	}
	if((nbyte = read(newsockfd,buffer,MAX_BUFFER)) == -1)
	{
		perror("Read Error!");
		exit(1);
	}
	buffer[nbyte] = '\0';
	printf("Message:\n%s\n",buffer);
	close(newsockfd);
	close(sockfd);
	return 0;

}
