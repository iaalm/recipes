/**************************************************
程序用途：角谷猜想穷举验证
编写者：simon
编写时间 2011-10-29 19:03
**************************************************/ 
#include <stdio.h>
#define M 1024

bool n[M]={false},a[M]={false};            //二进制表示的被计算数,a为计数器,n为参与与运算的数

bool ok(bool* t,int length);               //验证t是否为1(为角谷猜想结论) 
void binadd(bool *t,int length);           //相当于t++ 
void binm3Sub1(bool *t,int length);        //相当于t=t*3+1 
bool flag=true;                            //若未发生溢出为true,若溢出,停止程序 
long long now=0;                           //当前运算数,十进制表示 ,若以后采用更大的数组,可直接输出二进制,省去此变量 
int main()
{
    int i;
    do
    {
          binadd(a,M);
          now++;
          for(i=0;i<M;i++)
                 n[i]=a[i];
          while(!ok(n,M))
          {
                  if(n[0]==false)
                  {
                             for(i=1;i<M;i++)
                                             n[i-1]=n[i];
                  }
                  else
                             binm3Sub1(n,M);
          }
          if(now%10000==0) 
          printf("<%d is ok.\r",now);                         //每逢10000输出 
    }while(flag);
    printf("<%d is ok.\r",now);                               //溢出前确认正确的值 
    getchar();
    return 0;
}


bool ok(bool* t,int length)
{
     bool f=true;
     for(int i=1;i<length;i++)
     {
             if(*(t+i))
                     f=false;
     }
     if(f&&*t)
     return true;
     else
     return false;
}

void binadd(bool *t,int length)
{
     if(length==0)
     {
                  flag=false;
                  return;
     }
     if(!*t)
            *t=true;
     else
     {
         *t=false;
         binadd(++t,--length);
     }
}

void binm3Sub1(bool *t,int length)
{
     for(int i=M-1;i>0;i--)   //此处曾修改过 
     {
             if(*(t+i-1))
                      binadd(t+i,length-i);
     }
     binadd(t,length); 
}
