/*
ID: simonin1
LANG: C
TASK:crypt1
*/

#include<stdio.h>
#include<assert.h>

int check(short x,short *arph,short length)
{
	int i;
	for(i = 0;i < length;i++)
	        if(x == arph[i])
	                return 1;
	return 0;
}

int main()
{
	short arph[9],num,m1[3],m2[2],r1[3],r2[3],f[4];
	int result = 0;
	FILE *fp;

	fp = fopen("crypt1.in","r");
	fscanf(fp,"%hd",&num);
	for(f[0] = 0;f[0] < num;f[0]++)
	        fscanf(fp,"%hd",arph + f[0]);
	fclose(fp);
	
	for(m1[0] = 0;m1[0] < num;m1[0]++)
	{
        	for(m1[1] = 0;m1[1] < num;m1[1]++)
		{
			for(m1[2] = 0;m1[2] < num;m1[2]++)
			{
				for(m2[0] = 0;m2[0] < num;m2[0]++)
				{
					for(m2[1] = 0;m2[1] < num;m2[1]++)
					{
						r1[0] = arph[m1[0]] * arph[m2[0]];
						r1[1] = arph[m1[1]] * arph[m2[0]];
						r1[2] = arph[m1[2]] * arph[m2[0]];
						r2[0] = arph[m1[0]] * arph[m2[1]];
						r2[1] = arph[m1[1]] * arph[m2[1]];
						r2[2] = arph[m1[2]] * arph[m2[1]];
						
						f[0] = arph[m1[0]] * arph[m2[0]];
						f[1] = arph[m1[1]] * arph[m2[0]] + arph[m1[0]] * arph[m2[1]];
						f[2] = arph[m1[1]] * arph[m2[1]] + arph[m1[2]] * arph[m2[0]];
						f[3] = arph[m1[2]] * arph[m2[1]];

                                                r1[1] += (r1[0] / 10);
						r1[0] = r1[0] % 10;
						r1[2] += (r1[1] / 10);
						r1[1] = r1[1] % 10;
						r1[3] += (r1[2] / 10);
						r2[1] += (r2[0] / 10);
						r2[0] = r2[0] % 10;
						r2[2] += (r2[1] / 10);
						r2[1] = r2[1] % 10;
						r2[3] += (r2[2] / 10);
						//printf("%hd %hd %hd |%hd %hd |%hd %hd %hd %hd\n",arph[m1[2]],arph[m1[1]],arph[m1[0]],arph[m2[1]],arph[m2[0]],f[3],f[2],f[1],f[0]);
						f[1] += (f[0] / 10);
						f[0] = f[0] % 10;
						f[2] += (f[1] / 10);
						f[1] = f[1] % 10;
						f[3] += (f[2] / 10);
						f[2] = f[2] % 10;
						//printf("check!");
						if(check(r1[0],arph,num) && check(r1[1],arph,num) && check(r1[2],arph,num) && check(r2[0],arph,num) && check(r2[1],arph,num) && check(r2[2],arph,num) && check(f[0],arph,num) && check(f[1],arph,num) && check(f[2],arph,num) && check(f[3],arph,num))
						        result++;
					}
				}
			}
		}
	}
	
	fp = fopen("crypt1.out","w");
	fprintf(fp,"%d\n",result);
	fclose(fp);
	//getchar();
	return 0;
}
