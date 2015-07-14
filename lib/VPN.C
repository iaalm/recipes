#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	char *b,*c,*q=NULL;
	int n=0,i;
	if(argc == 0)
		return 1;
	n=strlen(argv[1]);
	b = (char*)malloc(sizeof(char) * (n + 3));
	c = (char*)malloc(sizeof(char) * (n + 40)); 

	for(i=0;i<n;i++)
	{
	   if(argv[1][i]==':')
	      if(argv[1][i+1]=='/' && argv[1][i+2]=='/')
	      {
		      argv[1] += (i + 3);
		      n -= (i + 3);
	      }
	}

	for(i=0;i<n;i++)
	if(argv[1][i]=='/')
	break;

	if(i!=n)
	{
	n=i;
	q=&argv[1][n+1];
	argv[1][i]=0;
	}

	for(i=0;i<n;i++)
	{
	if(argv[1][i]=='.')argv[1][i]=11;
	else if(argv[1][i]<='9')argv[1][i]-='0';
	else if(argv[1][i]<='Z')argv[1][i]=argv[1][i]-'A'+12;
	else argv[1][i]=argv[1][i]-'a'+38;
	}

	for(i=0;i<n;i++)
	{
	b[i]=argv[1][i]+i;
	b[i]%=64;
	if(b[i]<=9)b[i]+='0';
	else if(b[i]==10)b[i]='-';
	else if(b[i]==11)b[i]='.';
	else if(b[i]<=38)b[i]=b[i]-12+'A';
	else b[i]=b[i]-38+'a';
	}
	b[i]=0;

	c[0]=0;
	strcpy(c,"https://vpn.suda.edu.cn/,DanaInfo=.a");
	strcat(c,b);
	strcat(c,"+");
	if(q!=NULL)strcat(c,q);
	free(b);
	//free(c);
	//puts(c);
	n = fork();
	if(n == -1)
	{
		printf("Fork Error!");
		return 1;
	}
	if(n == 0)
		execlp("x-www-browser","x-www-browser",c,NULL);
	else
		free(c);
	return 0;
}
