/* by iaalm 2013
 * 实际相当于loader.c，当时用于测试前半部分汇编的初始化是否正常。
 *
 */
#include"s3c6410_my.h"

void start_armboot(){
	unsigned int t;
	U32(0x50000000) = 0x12345678;
	if(U32(0x50000000) != 0x12345678)
		while(1);
	GPMCON = 0x00222221;
	while(1){
		GPMDAT ^= 1;
		t = 1000000;
		while(t--);
	}
}
 void led(){
	GPMCON = 0x00222221;
	GPMDAT = 0;
 }
