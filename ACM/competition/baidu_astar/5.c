#include<stdio.h>
#include<string.h>

int main()
{
	int si,ti,c = 0;
	char source[200],target[200];
	scanf("%s",source);
	for(si = 0,ti = 0;si < strlen(source);si++,ti++)
	{
		if(c == 0)
		{
			if(source[si] == '_')
			{
				c = 1;
				si--;
				ti--;
			}
			else if(source[si] >= 'A' && source[si] <= 'Z')
			{
				c = 2;
				si--;
				ti--;
			}
			else if(source[si] >= 'a' && source[si] <= 'z')
			{
				target[ti] = source[si];
			}
			else
			{
				printf("Error!\n");
				return 0;
			}
		}
		else if(c == 1)
		{
			if(source[si] == '_')
			{
				si++;
				if(source[si] >= 'a' && source[si] <= 'z')
					target[ti] = source[si] + 'A' - 'a';
				else
				{
					printf("Error!\n");
					return 0;
				}
			}
			else if(source[si] >= 'a' && source[si] <= 'z')
			{
				target[ti] = source[si];
			}
			else
			{
				printf("Error!\n");
				return 0;
			}
		}
		else if(c == 2)
		{
			if(source[si] >= 'A' && source[si] <= 'Z')
			{
				target[ti++] = '_';
				target[ti] = source[si] + 'a' -'A';
			}
			else if(source[si] >= 'a' && source[si] <= 'z')
			{
				target[ti] = source[si];
			}
			else
			{
				printf("Error!\n");
				return 0;
			}
		}
	}
	target[ti] = '\0';
	printf("%s\n",target);
	return 0;
}
