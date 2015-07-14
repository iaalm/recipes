#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <stdio.h>
#include <stdlib.h> 
#define SERV_TCP_PORT 6601
#define EXIT_FAILURE 1
 
int main()
{
  int sockfd,len,s,n,i;
  struct sockaddr_in sa,ca;
  char buf[512];
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  sa.sin_port = htons(SERV_TCP_PORT);
 
  n = bind(sockfd, (struct sockaddr *) &sa, sizeof(sa)); 
  if(n == -1){
    perror("bind");  exit(EXIT_FAILURE);
  } 
  listen(sockfd,5);
  len = sizeof(ca);
  s = accept(sockfd, (struct sockaddr *) &ca, (socklen_t *) &len);
  printf("Connected\n");
 
  for(;;){
    n = recv(s,buf,sizeof(buf),0);
    buf[n] = 0;
    fputs(buf,stdout);  
    fflush(stdout); 
    for(i=0; i<n; i++)  buf[i] = toupper(buf[i]);
    send(s,buf,n,0);
  }
}
