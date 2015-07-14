#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
//#include<arpa/inet.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#define __USE_GNU
#include<assert.h>
#undef __USE_GNU

#define PORT 10001
#define MAX_BUF 4096
#define MAX_USER 1
int main()
{
	int sock_fd,newsock_fd,fp,nbyte,addr_len = sizeof(struct sockaddr_in),pid,stat;
	struct sockaddr_in addr;
	void *buffer = malloc(MAX_BUF);

	assert_perror((sock_fd = socket(AF_INET,SOCK_STREAM,0)) > 0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	assert_perror(bind(sock_fd,(struct sockaddr *)(&addr),sizeof(addr)) == 0);
	assert_perror(listen(sock_fd,MAX_USER) == 0);
	while(1)
	{
		//receive
		newsock_fd = accept(sock_fd,(struct sockaddr *)(&addr),&addr_len);
		puts("New connect!\n");
		fp = open("temp.c",O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR);
		while((nbyte = read(newsock_fd,buffer,MAX_BUF)) == MAX_BUF)
			write(fp,buffer,MAX_BUF);
		write(fp,buffer,nbyte);
		close(fp); 

		//compile
		if((pid = fork()) == 0)
			execlp("arm-linux-gcc","arm-linux-gcc","temp.c",0);
		waitpid(pid,&stat,0);
		if(stat != 0)	//compile error
		{
			write(newsock_fd,buffer,0);
			continue;
		}

		//transmit
		fp = open("a.out",O_RDONLY);
		while((nbyte = read(fp,buffer,MAX_BUF)) == MAX_BUF)
			write(newsock_fd,buffer,MAX_BUF);
		write(newsock_fd,buffer,nbyte);
		close(fp);
		close(newsock_fd);
	}
	return 0;
}
