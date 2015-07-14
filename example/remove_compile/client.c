#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<termios.h>
#define __USE_GNU
#include<assert.h>
#undef __USE_GNU
#define COMPILE_HOST "192.168.135.10"
#define PORT 10001
#define MAX_BUF 4096
#define MAX_USER 1
int main(int argc,char *argv[])
{
	int sock_fd,fp,nbyte,addr_len = sizeof(struct sockaddr_in);
	struct sockaddr_in addr;
	void *buffer = malloc(MAX_BUF);

	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	//assert_perror((sock_fd = socket(AF_INET,SOCK_STREAM,0)) != -1);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(COMPILE_HOST);

	//transmit
	connect(sock_fd,(struct sockaddr *)(&addr),addr_len);
	//assert_perror(connect(sock_fd,(struct sockaddr *)(&addr),addr_len) == 0);
	fp = open(argv[1],O_RDONLY);
	while((nbyte = read(fp,buffer,MAX_BUF)) == MAX_BUF)
		write(sock_fd,buffer,MAX_BUF);
	write(sock_fd,buffer,nbyte);
	close(fp);
	
	//receive
	fp = open("arm",O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU);
	while((nbyte = recv(sock_fd,buffer,MAX_BUF,0)) == MAX_BUF)
		write(fp,buffer,MAX_BUF);
	write(fp,buffer,nbyte);
	close(fp);
	close(sock_fd);
	return 0;
}
