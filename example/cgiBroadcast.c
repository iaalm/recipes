#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	char str[1024];
	int record;
	int i=0;
	bzero(str,1023);
	record=open("qrs",O_CREAT|O_RDWR);
	gets(str);
	if(str[10]!='\0')
	{
		while(str[i]!='\0')
		{
			if(str[i]=='+')
				str[i]=' ';
			else if(str[i]=='%')
			{
				str[i]=str[i+1]-(str[i+1]<='9'?'0':55);
				str[i]=str[i]*16+str[i+2]-(str[i+2]<='9'?'0':55);
				strcpy(&str[i+1],&str[i+3]);
			}

			i++;
		}
		lseek(record,0,SEEK_END);
		write(record,str,strlen(str));
		write(record,"</br>\n",6);
	}
	lseek(record,0,SEEK_SET);	
	puts("Content-type: text/html\n");
	puts("<html><head><title>IOT broadcast</title></head><body>");
	puts("<form action=\"/cgi-bin/test.cgi\" method=\"post\"> Questions:</br> <input type=\"text\" name=\"question\" /> <input type=\"submit\" value=\"Submit\"/> </form></br>");
	bzero(str,1024);
	while(read(record,str,1024)>0)
	{
		puts(str);
		bzero(str,1024);
	}
	puts("</body></html>");
	close(record);

	return 0;
}
