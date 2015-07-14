#include <stdio.h>
#include <fstream.h>
#define N 3

#define M 1

ofstream out("PointBeta2.log");
double b[N][N-M];


double A(int x,int y);


int main()

{
//printf("1!\n");
	int i,j,p,q;

	for(i=0;i<N;i++)

	{

		for(j=M;j<N;j++)

		{

			b[i][j-M]=A(i,j)*A(N-j,N-j)/1.0/A(N,N);
printf("\t%lf",b[i][j-M]);
		}

	}
	for(i=0;i<N;i++)

	{

		for(j=M+1;j<N;j++)

		{

			for(p=0;p<N;p++)
			{
				for(q=M;q<j;q++)
				{
//printf("%lf ",b[i][j]);
					if(i!=p)b[i][j-M]-=b[p][q-M];
				}
			}
		}

	}
printf("3\n");
	for(i=0;i<N;i++)

	{

		printf("%d:",i);
		for(j=M;j<N;j++)

		{

			printf("\t%lf",b[i][j-M]);

		}

		printf("\n");
	}

    getchar();getchar();

}


double A(int x,int y)
{
//printf("%d,%d|",x,y);
	double z=1;
	if(x<y)return 0;
	for(int p=x;p>x-y;p--)z*=p;
	return z;
}
