//测试纯运行printf时的速度，约6000次/秒
#include <stdio.h>

int main()
{
    for(unsigned int i=0;;i++)
    printf("%d\r",i);
}
