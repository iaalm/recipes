#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("error");
		getchar();
		exit(0);
	}
	unsigned char t;
	FILE *in = fopen(argv[1],"rb");

	FILE *out = fopen(strcat(argv[1],"_"),"wb");
 	fread(&t,1,1,in);
	while(!feof(in))
	{
		t = ~t;
		fwrite(&t,1,1,out);
  		fread(&t,1,1,in);
	}
	fclose(in);
	fclose(out);
	
	return 0;
}
