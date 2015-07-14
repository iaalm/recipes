//角谷函数系列的原型，其他值提高了数据的范围，但效率远不及此程序。
//对于我们这个水平层次的人来说，自行优化代码不算个好主意。
//以后可以尝试以汇编写此程序，应当有所提升。 

#include <stdio.h>

unsigned a=0,n=0;               //只需修改此处的数据类型 
bool flag=true;

int main()
{
    do
    {
    a++;
    n=a;
    while(n!=1)
    {
               if(a>n)break; 
               if(n%2==0)
               n=n/2;
               else
               n=n*3+1;
    }
    if(a%100000000==0)
    printf("<%d is ok\r",a);
    }
    while(flag);
}
