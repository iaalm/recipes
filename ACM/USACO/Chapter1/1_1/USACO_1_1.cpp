/*
ID: simonin1
LANG: C
TASK: ride
*/
#include <stdio.h>

int main()
{
    unsigned int comet = 1,group = 1;
    char in[7],t = 0;
    FILE* fp = fopen("ride.in","r");
    fscanf(fp,"%s",in);
    do
    {
            comet *= in[t] - 'A' + 1;
            t++;
    }while(in[t] != '\0');
    comet = comet % 47;
    fscanf(fp,"%s",in);
    fclose(fp);
    t = 0;
    do
    {
            group *= in[t] - 'A' + 1;
            t++;
    }while(in[t] != '\0');
    group = group % 47;
    fp =fopen("ride.out","w");
    if(group == comet)
            fprintf(fp,"GO\n");
    else
            fprintf(fp,"STAY\n");
    fclose(fp);
    return 0;
}
