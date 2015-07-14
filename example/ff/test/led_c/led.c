#include"s3c6410.h"

__attribute__ ((noreturn)) void main(){
	unsigned int t;
	GPMCON = 0x00221111;
	while(1){
		GPMDAT ^= 0xf;
		t = 1000000;
		while(t--);
	}
}
