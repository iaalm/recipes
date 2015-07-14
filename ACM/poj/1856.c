#include<stdio.h>

int main()
{
	char map[1000][1001],t;
	int w,h,i,j,k,l,m,count;
	while(1)
	{
end:		count = 0;
		scanf("%d %d",&h,&w);
		if(h == 0)
			return 0;
		getchar();
		for(i = 0;i < h;i++)
			gets(map[i]);
		for(i = 0;i < h;i++)
			for(j = 0;j < w;j++)
				if(map[i][j] == '#')
				{
					for(l = j + 1;l < w;l++)
						if(map[i][l] != '#')
							break;
					for(k = i;;k++)
					{
						t = map[k][j];
						map[k][j] = '.';
						for(m = j + 1;m < l;m++)
							if(map[k][m] == t)
								map[k][m] = '.';
							else
							{
								printf("Bad placement.\n");
								goto end;
							}
						if((j > 0 && map[k][j - 1] == '#') || (l  !=  w && map[k][l] == '#'))
						{
							printf("Bad placement.\n");
							goto end;
						}
						if(t == '.' || k == h -1)
						{
							if(i > 0 && ((j > 0 && map[i -1][j-1] == '#') || (l != w && map[i -1][l] == '#')))
							{
								printf("Bad placement.\n");
								goto end;
							}
							count++;
							j = l - 1;
							break;
						}
					}
				}
		printf("There are %d ships.\n",count);
	}
}
