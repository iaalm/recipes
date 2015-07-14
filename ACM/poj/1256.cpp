#include<stdio.h>
#include<string.h>

int n;
const char charset[52] = {'A','a','B','b','C','c','D','d','E','e','F','f','G','g','H','h','I','i','J','j','K','k','L','l','M','m','N','n','O','o','P','p','Q','q','R','r','S','s','T','t','U','u','V','v','W','w','X','x','Y','y','Z','z'};
char a[14];
int set[52];

void w(int);

int main()
{
	int i,N;
	scanf("%d",&N);
	while(N--)
	{
		scanf("%s",a);
		n = strlen(a);
		memset(set,0,sizeof(set));
		for(i = 0;i < n;i++)
		{
			if(a[i] <= 'Z')
				set[(a[i] - 'A') * 2]++;
			if(a[i] >= 'a')
				set[(a[i] - 'a')  * 2 + 1]++;
		}
		w(0);
	}
	return 0;
}

void w(int t)
{
	int i;
	if(t == n)
	{
		printf("%s\n",a);
		return;
	}
	for(i = 0;i < 52;i++)
	{
		if(set[i])
		{
			set[i]--;
			a[t] = charset[i];
			w(t + 1);
			set[i]++;
		}
	}
}
