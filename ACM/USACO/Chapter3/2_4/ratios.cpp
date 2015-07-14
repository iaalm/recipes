/*
ID: simonin1
LANG: C++
TASK: ratios
*/

#include<stdio.h>
#include <string.h>
/*
 * 不要相信这过程阿
 * 有很多漏洞，数据若而已
*/
struct fs{
	int m,z;
};

int ojld(int a,int b){
	int t;
	do{
		t = a % b;
		a = b;
		b = t;
	}while(t);
	return a;
}

int main(int argc, const char *argv[])
{
	int input[3][4],temp[3][4],i,j,k,l,m,n;
	fs res[3];
	
	FILE* fp = fopen("ratios.in","r");
	for(j = 0;j < 3;j++)
		fscanf(fp,"%d",&input[j][3]);
	for(i = 0;i < 3;i++)
		for(j = 0;j < 3;j++)
			fscanf(fp,"%d",&input[j][i]);
	fclose(fp);
	memcpy(temp,input,3 * 4 * sizeof(int));

	/*
	   for(m = 0;m < 3;m++){
	   for(n = 0;n < 4;n++)
	   printf("%d ",temp[m][n]);
	   putchar(10);
	   }
	   putchar(10);
	   */
	for(i = 0;i < 2;i++)
		for(k = i + 1;k < 3;k++){
			for(j = i + 1;j < 4;j++)
				temp[k][j] = temp[k][j] * temp[i][i] - temp[i][j] * temp[k][i];
		}

	l = ojld(temp[2][2],temp[2][3]);
	res[2].z = temp[2][3] / l;
	res[2].m = temp[2][2] / l;
	res[1].z = temp[1][3] * res[2].m - temp[1][2] * res[2].z;
	res[1].m = res[2].m * temp[1][1];
	res[0].z = temp[0][3] * res[1].m - temp[0][2]  * res[1].m / res[2].m * res[2].z - temp[0][1] * res[1].z;
	res[0].m = res[1].m * temp[0][0];
	
	for(i = 0;i < 3;i++){
		if(res[i].z){
			k = ojld(res[i].m,res[i].z);
			res[i].z /= k;
			res[i].m /= k;
		}
	}
	l = 1;
	for(i = 0;i < 3;i++){
		if(res[i].z){
			k = ojld(res[i].m,l);
			l *= res[i].m / k;
		}
	}
	for(i = 0;i < 3;i++){
		res[i].z *= l / res[i].m;
	}

	fp = fopen("ratios.out","w");
	if(res[0].z >= 0 && res[1].z >= 0 && res[2].z >= 0 && res[0].m >= 0){
		for(i = 0;i < 3;i++)
			fprintf(fp,"%d ",res[i].z);
		fprintf(fp,"%d\n",l);
	}
	else
		fprintf(fp,"NONE\n");
	fclose(fp);
	return 0;
}

