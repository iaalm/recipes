/*
ID: simonin1
LANG: C
TASK:castle
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int *room,*in,m,n,NumRoom = 0;

void FindRoom(int i);

int main()
{
	int i,j,unfinish,maxroom = 0,maxrooms = 0,x,y;
	char d;
	FILE  *fp = fopen("castle.in","r");
	fscanf(fp,"%d %d",&m,&n);
	in = (int *)malloc(sizeof(int) * m * n);
	room = (int *)malloc(sizeof(int) * m * n);
	for(i = 0;i < m * n;i++)
	{
	        fscanf(fp,"%d", in + i);
		assert(i >= 0 && i < m * n);
	        room[i] = 0;
	}
	fclose(fp);
	
	do
	{
		unfinish = 0;
		for(i = 0;i < m * n;i++)
		{
			if(room[i] == 0)
			{
				NumRoom++;
				unfinish = 1;
				FindRoom(i);
			}	
		}
	}
	while(unfinish);

	int *num = (int*) malloc(sizeof(int) * (NumRoom + 1));
	for(i = 1;i <= NumRoom;i++)
	{
		num[i] = 0;
		for(j = 0;j < m * n;j++)
			if(room[j] == i)
				num[i]++;
		if(num[i] > maxroom)
			maxroom = num[i];
	}

	for(i = 0;i < m * n;i++)
	{
		j = (n - 1 - i % n) * m + i / m;
		if(j > m && room[j] != room[j - m])
		{
			unfinish = num[room[j]] + num[room[j - m]];
			if(unfinish > maxrooms)
			{
				maxrooms = unfinish;
				x = j / m + 1;
				y = j % m + 1;
				d = 'N';
			}
		}
		if((j + 1) % m != 0 && room[j] != room[j + 1])
		{
			unfinish = num[room[j]] + num[room[j + 1]];
			if(unfinish > maxrooms)
			{
				maxrooms = unfinish;
				x = j / m + 1;
				y = j % m + 1;
				d = 'E';
			}
		}
	}
	
	fp = fopen("castle.out","w");
	fprintf(fp,"%d\n%d\n%d\n%d %d %c\n",NumRoom,maxroom,maxrooms,x,y,d);
	fclose(fp);

	free(in);
	free(room);
	free(num);
	return 0;
}

void FindRoom(int i)
{
	room[i] = NumRoom;
	if((in[i] & 1) == 0 && room[i - 1] == 0)
	{
		FindRoom(i - 1);
	}
	if((in[i] & 2) == 0 && room[i - m] == 0)
	{
		FindRoom(i - m);
	}
	if((in[i] & 4) == 0 && room[i + 1] == 0)
	{
		FindRoom(i + 1);
	}
	if((in[i] & 8) == 0 && room[i + m] == 0)
	{
		FindRoom(i + m);
	}
}
