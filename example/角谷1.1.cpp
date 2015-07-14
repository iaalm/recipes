/**************************************************
程序用途：角谷猜想穷举验证
版本号：1.1 
编写者：simon
编写时间 2011-10-29 19:03
更新记录：1.0：基于bool型的实现，210000条/分钟； 
          1.1：改进了binm3Sub1函数使其执行一遍除二操作.，每次减少1024次通过for实现的移位操作，未能避免反向加和产生的binadd函数中连环进位 ，但可达到大约910000条/分钟 
备注：打开DEV-CPP最大优化，生成奔腾4代码，运行于许洋光的ASUS-X42J笔记本（Intel core i3-370M 2.4GHz，2G）上 
**************************************************/ 
/* TODO (#1#): 避免反向加和产生的binadd函数中连环进位  */
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
#ifdef DEBUG
            for(i=7;i>=0;i--)
                         printf("%d",n[i]);
            printf("\n");
#endif
                  if(n[0]==false)
                  {
                             for(i=1;i<M;i++)
                                             n[i-1]=n[i];
                  }
                  else
                             binm3Sub1(n,M);
          }
#ifndef DEBUG
          if(now%10000==0) 
#endif
          printf("<%d is ok.\r",now);                         //每逢10000输出 
    }while(flag);
    printf("<%d is ok.\r",now); 
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
     for(int i=length-1;i>0;i--)
     {
             if(*(t+i+1))
                      binadd(t+i,length-i);
     }
     binadd(t,length); 
}
