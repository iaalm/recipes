/*
ID: simonin1
LANG: C
TASK: palsquare
*/
#include<stdio.h>
#define LENGTH 20
#define M 300
//#define DEBUG
typedef struct
{
        short num[LENGTH];
} Num;

void add1(Num *n,short base);
Num Square(Num num,short base);
int IsPalindrom(Num n);
void PrintNum(FILE *fp,Num num,Num square);
int NumLen(Num num);

int main()
{
    Num num,square;
    int n,i;
    FILE *fp = fopen("palsquare.in","r");
#ifdef DEBUG
    FILE *debug = fopen("palsquare.tmp","w");
#endif
    fscanf(fp,"%d",&n);
    fclose(fp);
    
    fp = fopen("palsquare.out","w");
    for(i = 0;i < LENGTH;i++)
    {
          num.num[i] = '0';
          square.num[i] = '0';
    }
    for(i = 1;i <= M;i++)
    {
          add1(&num,n);
          square = Square(num,n);
#ifdef DEBUG
    PrintNum(debug,num,square);
#endif
          if(IsPalindrom(square))
                 PrintNum(fp,num,square);
    }
#ifdef DEBUG

#endif
    fclose(fp);
    return 0;
}

void add1(Num *n,short base)
{
     int i;
     char Nbase = base + '0';
     (*n).num[0]++;
     for(i = 0;i < LENGTH;i++)
     {
             if((*n).num[i] >= Nbase)
             {
                         (*n).num[i] -= base;
                         
                         (*n).num[i + 1]++;
             }
             else
                         break;
     }
}

Num Square(Num num,short base)
{
    Num result;
    int i,j,acc = 0,n = NumLen(num);
    for(i = 0;i < LENGTH;i++)
          result.num[i] = '0';
    for(i = 0;i <= n;i++)
    {
          acc = 0;
          for(j = 0;j <= n;j++)
          {
                result.num[i + j] += ((num.num[i] - '0') * (num.num[j] - '0') + acc);
                acc = (result.num[i + j] - '0') / base;
                result.num[i + j] = (result.num[i + j] - '0') % base + '0';
          }
          result.num[i + j] += acc;
    }
    return result;
}

int IsPalindrom(Num num)
{
    int n,i,half;
    n = NumLen(num);
    half = n / 2;
    for(i = n;i > half;i--)
    {
          if(num.num[i] != num.num[n - i])
                      return 0;
    }
    return 1;
}

void PrintNum(FILE *fp,Num num,Num square)
{
      int n;
      n = NumLen(num) + 1;
      do
      {
              n--;
              if(num.num[n] <= '9') 
                      fputc((char)num.num[n],fp);
              else
                      fputc((char)(num.num[n] - '9' - 1 + 'A'),fp);
      }while(n != 0);
      
      fprintf(fp," ");
      
      n = NumLen(square) + 1;
      do
      {
              n--;
              if(square.num[n] <= '9') 
                      fputc((char)square.num[n],fp);
              else
                      fputc((char)(square.num[n] - '9' - 1 + 'A'),fp);
      }while(n != 0);
      
      fprintf(fp,"\n");
}

int NumLen(Num num)
{
    int n;
    for(n = LENGTH - 1;;n--)
          if(num.num[n] != '0')
                      break;
    return n;
}
