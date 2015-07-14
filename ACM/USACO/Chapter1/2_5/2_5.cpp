/*
ID: simonin1
LANG: C
TASK: dualpal
*/
#include<stdio.h>
#define M 20

//#define DEBUG

int IsPalindrom(int num,short base);
int TimeOfPalindrom(int num);

#ifdef DEBUG
FILE *debug = fopen("dualpal.tmp","w");
#endif

int main()
{
    int n,max,count = 0;
    FILE *fp = fopen("dualpal.in","r");
    fscanf(fp,"%d",&max);
    fscanf(fp,"%d",&n);
    fclose(fp);
    
    fp = fopen("dualpal.out","w");
    
    do
    {
         n++;
         if(TimeOfPalindrom(n) > 1)
         {
                 count++;
                 fprintf(fp,"%d\n",n);
         }
    }while(count != max);
    
    fclose(fp);
    
#ifdef DEBUG
    fclose(debug);
#endif
    
    return 0;
}

int TimeOfPalindrom(int num)
{
    short base;
    int result = 0;
    for(base = 2;base <= 10;base++)
    {
          result += IsPalindrom(num,base);
          if(result == 2)
               break;
    }
    return result;
}

int IsPalindrom(int num,short base)
{
    
#ifdef DEBUG
    fprintf(debug,"number:%4d,base:%2d:",num,base);
#endif
    short numbers[M],length = 0,i,half;
    do
    {
          numbers[length] = num % base;
          num /= base;
          length++;
    }while(num != 0);
    half = length / 2;
    length--;
    
#ifdef DEBUG
    for(i = length;i >= 0;i--)
    {
        fprintf(debug,"%d",numbers[i]);
    }
    fprintf(debug,"  length:%d\n",length);
#endif

    for(i = 0;i < half;i++)
    {
          if(numbers[i] != numbers[length - i])
                  return 0;
    }
    return 1;
}
