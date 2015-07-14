#include  <unistd.h>
#include  <sys/types.h>
#include  <stdio.h>

#define  M  32

int  jg(int  No,int  Num);
bool  n[M]={false},a[M]={false};                        //¶þœøÖÆ±íÊŸµÄ±»ŒÆËãÊý,aÎªŒÆÊýÆ÷,nÎª²ÎÓëÓëÔËËãµÄÊý
bool  aBigThann(bool  *  a,bool  *n  ,int  length);  
bool  ok(bool*  t,int  length);                              //ÑéÖ€tÊÇ·ñÎª1(ÎªœÇ¹È²ÂÏëœáÂÛ)  
void  binadd(bool  *t,int  length);                      //Ïàµ±ÓÚt++  
void  binm3Sub1(bool  *t,int  length);                //Ïàµ±ÓÚt=t*3+1  
bool  flag=true;                                                        //ÈôÎŽ·¢ÉúÒç³öÎªtrue,ÈôÒç³ö,Í£Ö¹³ÌÐò  
long  long  now=0;                                                      //µ±Ç°ÔËËãÊý,Ê®œøÖÆ±íÊŸ  ,ÈôÒÔºó²ÉÓÃžüŽóµÄÊý×é,¿ÉÖ±œÓÊä³ö¶þœøÖÆ,Ê¡È¥ŽË±äÁ¿  
int  jg(int  No,int  Num)
{
	if(No>Num)
	return 1;
        int  i,j;
        do
        {
		for(i=0;i<No;i++)
		{
                    binadd(a,M);
                    now++;
		}
                    for(i=0;i<M;i++)
                                  n[i]=a[i];
                    while(!ok(n,M))
                    {
#ifdef  DEBUG
                        for(i=7;i>=0;i--)
                                                  printf("%d",n[i]);
                        printf("\n");
#endif
                                    if(aBigThann(a,n,M))
                                    {
                                                                  break;                                                      //nÐ¡ÓÚaÊ±±Ø¿É³ÉÁ¢  
                                    }
                                    if(!n[0])
                                    {
                                                          for(i=0;!n[i];i++){}
                                                          for(j=i-1;j<M;j++)
                                                                                          n[j-1]=n[j];
                                    }
                                    else
                                                          binm3Sub1(n,M);
                    }
#ifndef  DEBUG
                    if(now%1000000==0)  
#endif
                    printf("<%d  is  ok.Thread %d\n",now,No);                                                  //Ã¿·ê10000Êä³ö  

		for(i=0;i<Num;i++)
		{
                    binadd(a,M);
                    now++;
		}
        }while(flag);
        printf("<%d  is  ok.\r",now);  
        getchar();
        return  0;
}


bool  ok(bool*  t,int  length)
{
          bool  f=true;
          for(int  i=1;i<length;i++)
          {
                          if(*(t+i))
                                          f=false;
          }
          if(f&&*t)
          return  true;
          else
          return  false;
}

void  binadd(bool  *t,int  length)
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

void  binm3Sub1(bool  *t,int  length)
{
          for(int  i=length-1;i>0;i--)
          {
                          if(*(t+i+1))
                                            binadd(t+i,length-i);
          }
          binadd(t,length);  
}
bool  aBigThann(bool  *  a,bool  *n  ,int  length)
{
          for(int  i=length-1;i>=0;i--)
          {
                          if(*(a+i)!=*(n+i))
                          {
                                                              if(*(a+i))
                                                              return  true;
                                                              else
                                                              return  false;
                          }
          }
          return  false;
}


int  main()
{
	int  NumOfThread,pid,ErrorNum;
	printf("请输入线程数\n");
	scanf("%d",&NumOfThread);
	for(int  i=0;i<NumOfThread;i++)
	{
		pid=fork();
		if(pid==-1)
			printf("fork  error!\n");
		else  if(pid==0)
		{	
			ErrorNum=jg(i,NumOfThread);			
			break;
		}
	}	
	return  0;
}
