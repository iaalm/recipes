#include<time.h>

void delay(unsigned int)
{
        time_t start,end;
	start = time((time_t*) NULL);
	do
	{
		end = time((time_t*) NULL);
	}while(end <= start + 5);
}
