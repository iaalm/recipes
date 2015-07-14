/*
ID: simonin1
LANG: C
TASK: friday
*/
#include <stdio.h>
#include <assert.h>

int weekday(int t,int days);
int monthday(int year,int month);

int main()
{
	int result[7] = {0},NumYear,year = 1900,month = 1,day =6;        //1234567
	FILE *fp = fopen("friday.in","r");
	fscanf(fp,"%d",&NumYear);
	NumYear += 1900;
	fclose(fp);
	do
	{
		do
		{
			result[day]++;
			day = weekday(day,monthday(year,month++));
		}while(month != 13);
		month = 1;
		year++;
	}while(year < NumYear);
	fp = fopen("friday.out","w");
	fprintf(fp,"%d %d %d %d %d %d %d\n",result[6],result[0],result[1],result[2],result[3],result[4],result[5]);
	fclose(fp);
	return 0;
}

int weekday(int t,int days)
{
	t += (days % 7);
	t %= 7;
	return t;
}

int monthday(int year,int month)
{
	assert(month <=12);
	if(month == 1||month == 3||month == 5||month == 7||month == 8||month == 10||month == 12)
		return 31;
	else if(month == 4||month == 6||month == 9||month == 11)
		return 30;
	else if(year % 4 == 0&&(year % 100 != 0||year % 400 == 0))
		return 29;
	else
		return 28;
}