#include<stdio.h>
#include<string.h>
#define CA_MAX 110
int main()
{
	char res[CA_MAX],ad[101];
	int len,ri,ai,acc;
	memset(res,0,sizeof(res));
	while(1)
	{
		gets(ad);
		len = strlen(ad);
		if(len == 1 && ad[0] == '0')
			break;
		for(acc = 0,ri = 0,ai = len - 1;ai >= 0;ri++,ai--)
		{
			acc = res[ri] + ad[ai] - '0'  + acc;
			res[ri] = acc % 10;
			acc /= 10;
		}
		while(acc)
		{
			acc = res[ri] + acc;
			res[ri] = acc % 10;
			acc /= 10;
			ri++;
		}
	}
	for(ri = CA_MAX - 1;ri > 0;ri--)
		if(res[ri])
			break;
	for(ai = ri;ai >= 0;ai--)
		printf("%d",res[ai]);
	putchar(10);
	return 0;
}
