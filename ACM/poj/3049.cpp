#include<stdio.h>

int main()
{
	char str[300];
	int i,sum;
	while(1)
	{
		gets(str+1);
		if(str[1] == '#')
			break;
		sum = 0;
		for(i = 1;str[i] != '\0';i++)
			if(str[i] != ' ')
				sum += i * (str[i] - 'A' + 1);
		printf("%d\n",sum);
	}
	return 0;
}
