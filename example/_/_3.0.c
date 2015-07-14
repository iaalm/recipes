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
	char name[1024];
	unsigned char t;
	unsigned long i;
	FILE *in = fopen(argv[1],"rb");

 	for(i =0;;i++)
 	{
		if(argv[1][i] == '\0')
		{
			if(argv[1][i - 1] == '_')
			{
				name[i - 1] = '\0';
			}
			else
			{
				name[i] = '_';
				name[i + 1] = '\0';
			}
			break;
		}
		name[i] = argv[1][i];
	}

	FILE *out = fopen(name,"wb");
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
