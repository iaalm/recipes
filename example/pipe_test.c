/*
 *向一个管道中同时输入数据,导致数据完整性问题,经测试，管道缓冲区位4K
 */
#include<unistd.h>
#define BUF_SIZE 500000
int main(int argc, const char *argv[])
{
	int p[2],i;
	char temp,str[BUF_SIZE];
	pipe(p);
	if(fork()){
		while(1){
			read(p[0],&temp,1);
			write(1,&temp,1);
		}
	}
	else{
		if(fork())
			temp = 'A';
		else
			temp = 'B';
		for(i = 0;i < BUF_SIZE;i++)
			str[i] = temp;
		write(p[1],str,BUF_SIZE);
	}
	return 0;
}
