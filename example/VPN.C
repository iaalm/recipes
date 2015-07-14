#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
char a[100],b[100],c[100],*q=NULL;
int n=0,i;
puts("输入域名或IP地址\n");
scanf("%s",a);
n=strlen(a);

for(i=0;i<n;i++)
{
   if(a[i]==':')
      if(a[i+1]=='/' && a[i+2]=='/')
      {
         puts("不要含有协议名\n");
         return 0;
      }
}

for(i=0;i<n;i++)
if(a[i]=='/')
break;

if(i!=n)
{
n=i;
q=&a[n+1];
a[i]=0;
}

for(i=0;i<n;i++)
{
if(a[i]=='.')a[i]=11;
else if(a[i]<='9')a[i]-='0';
else if(a[i]<='Z')a[i]=a[i]-'A'+12;
else a[i]=a[i]-'a'+38;
}

for(i=0;i<n;i++)
{
b[i]=a[i]+i;
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
puts(c);
return 0;
}
