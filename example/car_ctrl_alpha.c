#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<termios.h>
#include<assert.h>
#define PORT 9400
#define MAX_BUFFER 1024
#define DEBUG
int sockfd,newsockfd;
#ifdef DEBUG
void STOPSIG()
{
	puts("\nSTOPSIG");
	close(newsockfd);
	close(sockfd);
	exit(0);
}
#endif
int main()
{
#ifdef DEBUG
	signal(SIGINT,STOPSIG);
#endif
	int nbyte;
	unsigned char sendbuf[4][7];
	sendbuf[0][0] = sendbuf[1][0] = 0xff;
	sendbuf[0][1] = sendbuf[1][1] = sendbuf[1][3] = 2;
	sendbuf[0][2] = sendbuf[1][2] = sendbuf[0][3] = 1;
	sendbuf[0][5] = sendbuf[1][5] = 0;
	sendbuf[2][0] = 0xff;
	sendbuf[2][1] = 0x08;
	sendbuf[2][2] = 0x01;
	sendbuf[2][3] = 0x00;
	sendbuf[2][4] = 0x00;
	sendbuf[2][5] = 0x00;
	sendbuf[2][6] = 0x09;

	sendbuf[3][0] = 0xff;
	sendbuf[3][1] = 0x02;
	sendbuf[3][2] = 0x01;
	sendbuf[3][3] = 0x01;
	sendbuf[3][4] = 0x30;
	sendbuf[3][5] = 0x00;
	sendbuf[3][6] = 0x34;

	int fp = open("/dev/console",O_WRONLY);
	struct termios opt;
	if(tcgetattr(fp, &opt) != 0)
    	{
        	perror("tcgetattr fd");
		exit(1);
    	}
	tcflush(fp,TCIOFLUSH);
	cfsetispeed(&opt,B115200);
	cfsetospeed(&opt,B115200);
	if(tcsetattr(fp, TCSANOW, &opt) != 0)
        {
        	perror("tcsetattr fd");
                return;
        }
	tcflush(fp,TCIOFLUSH);
	assert(fp > 0);
	write(fp,sendbuf[2],7);
	write(fp,sendbuf[3],7);
	signed char left,right,t;
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
	while((newsockfd = accept(sockfd,(struct sockaddr *)(&addr),&addr_len)) >= 0)
	{
		printf("new socket id:%d\n",newsockfd);
		if((nbyte = read(newsockfd,buffer,MAX_BUFFER)) > 0)
		{
			buffer[nbyte] = '\0';
			printf("GET%d:\n%s\n",nbyte,buffer);
			if(/*nbyte == 8 && */buffer[0] == '@' && buffer[7] == '#')
			{
				sscanf(buffer + 2,"%X",&left);
				sscanf(buffer + 5,"%X",&right);
				if(buffer[1] == '-')
					left = - left;
				if(buffer[4] == '-')
					right = - right;
				//printf("%c%c%c%c%c%c%c\n",0xff,2,0,1,left,0,0);
				//printf("%c%c%c%c%c%c%c\n",0xff,2,0,2,right,0,0);
				sendbuf[0][4] = left;
				sendbuf[1][4] = right;
				sendbuf[0][6] = ((unsigned char)left) + 4;
				sendbuf[1][6] = ((unsigned char)right) + 5;
				write(fp,sendbuf[0],7);
				usleep(50000);
				write(fp,sendbuf[1],7);
			}
			else
				puts("Message ERROR");
			close(newsockfd);
		}
		else
		{
			perror("Read Error");
			exit(1);
		}
	}
	printf("Read Finish!\n");
	close(sockfd);
	return 1;
}
