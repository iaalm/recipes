#include<stdio.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("error");
		getchar();
		exit(0);
	}
	FILE *fp = fopen(argv[1],"r");
	char t;
	while(!feof(fp))
	{
		fscanf(fp,"%c",&t);
		printf("%c",t);
	}
	getchar();
	return 0;
}
