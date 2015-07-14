/*
ID: simonin1
LANG: C
TASK:ttwo
*/

#include<stdio.h>

int main()
{
	char map[10][11];
	short c = 0,f = 0,cx,cy,fx,fy,i,j;   // 0 = N,1 = E,2 = S,3 = W
	int time;
	FILE *fp = fopen("ttwo.in","r");
	for(time = 0;time < 10;time++)
	        fscanf(fp,"%s",map[time]);
	fclose(fp);
	for(i = 0;i < 10;i++)
		for(j = 0;j < 10;j++)
		{
			if(map[i][j] == 'C')
			{
				cx = i;
				cy = j;
			}
			if(map[i][j] == 'F')
			{
				fx = i;
				fy = j;
			}
		}
	for(time = 1;time < 160001;time++)      //answer cannot bigger than 4 * 10 *10 * 4 * 10 *10 = 160000
	{
		c %= 4;
		f %= 4;
		switch(c)
		{
			case 0:
				if(cx != 0 && map[cx - 1][cy] != '*')
				        cx--;
    				else
    				        c++;
				break;
			case 1:
				if(cy != 9 && map[cx][cy + 1] != '*')
				        cy++;
    				else
    				        c++;
				break;
			case 2:
				if(cx != 9 && map[cx + 1][cy] != '*')
				        cx++;
    				else
    				        c++;
				break;
			case 3:
				if(cy != 0 && map[cx][cy - 1] != '*')
				        cy--;
    				else
    				        c++;
				break;
		}
		switch(f)
		{
			case 0:
				if(fx != 0 && map[fx - 1][fy] != '*')
				        fx--;
    				else
    				        f++;
				break;
			case 1:
				if(fy != 9 && map[fx][fy + 1] != '*')
				        fy++;
    				else
    				        f++;
				break;
			case 2:
				if(fx != 9 && map[fx + 1][fy] != '*')
				        fx++;
    				else
    				        f++;
				break;
			case 3:
				if(fy != 0 && map[fx][fy - 1] != '*')
				        fy--;
    				else
    				        f++;
				break;
		}
		
		if(cx == fx && cy == fy)
		break;
	}
	if(time == 160001)
		time = 0;
	fp = fopen("ttwo.out","w");
	fprintf(fp,"%d\n",time);
	fclose(fp);
	
	return 0;
}
