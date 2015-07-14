#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
 
#define SERV_HOST_ADDR "192.168.135.67"
#define SERV_TCP_PORT 6601
 
int main()
{
  int sockfd,n;
  struct sockaddr_in sa;
  char sendline[512],buf[512];
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
  bzero((char *)&sa, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr=inet_addr(SERV_HOST_ADDR);
  sa.sin_port=htons(SERV_TCP_PORT);
 
  connect(sockfd, (struct sockaddr *) &sa, sizeof(sa));
  printf("Connected\n");
  for(;;){
    fgets(sendline, 512, stdin);
    n = strlen(sendline);
    send(sockfd, sendline,n, 0);
 
    n = recv(sockfd,buf,sizeof(buf),0);
    buf[n] = 0;
    fputs(buf, stdout);  fflush(stdout);
  }
}
