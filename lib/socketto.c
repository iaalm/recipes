#include<stdio.h>
#include"mysocket.h"
#define BUFFER_SIZE 8400

int main(int argc, char *argv[])
{
	int socket,port = -1,nbyte;
	char buffer[BUFFER_SIZE];
	if(argc != 3)
	{
		fputs("Usage: socketto IP PORT",stderr);
		return 1;
	}
	sscanf(argv[2],"%d",&port);
	if(port <= 0 || port > 65535)
	{
		fputs("port isn't correct!",stderr);
		return 1;
	}
	socket = open_clientfd(argv[1],port);
	switch(socket)
	{
		case -1:
			perror("ERROR:");
			return 1;
		case -2:
			fputs("host name error!",stderr);
			return 1;
	}
	fputs("start sending\n",stderr);
	while((nbyte = read(0,buffer,BUFFER_SIZE)) != 0)
	{
		send(socket,buffer,nbyte,0);
		fprintf(stderr,"%d byte(s) sent\n",nbyte);
	}
	fputs("finished",stderr);
	return 0;
}
