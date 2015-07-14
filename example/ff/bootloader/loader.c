#include"s3c6410_my.h"

void start_armboot(){
	U32(MEM_BASE) = 0xff;
	CopyMMCtoMem(1,0,10,MEM_BASE,0);
	if(U32(MEM_BASE) == 0xff){
		while(1);
	}


	//这里最好是清理堆栈，用返回方式开始内核，但是这需要使用汇编代码调用CopyMMCtoMem函数,比较麻烦，先将就一下。
	
	((int (*)(int,char**))MEM_BASE)(0,NULL);




	unsigned int t;
	U32(GPMCON) = 0x00222221;
	while(1){
		U32(GPMDAT) ^= 1;
		t = 1000000;
		while(t--);
	}
}
