#include<stdio.h>

int main()
{
	char name[127];
	unsigned char t;
	scanf("%s",name);
	FILE *in = fopen(name,"rb");
	
	for(t = 0;name[t] != '\0';t++);
	name[t] = '_';
	name[t + 1] = '\0';

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
