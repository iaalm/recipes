typedef char bool;

#define NULL 0

#define U32(ADDR) (*(unsigned int*)(ADDR))

#define GPMCON		0x7f008820
#define GPMDAT		0x7f008824
#define P1MEMSTAT	0x7E001000
#define P1DIRECTCMD	0x7E001008
#define MEM_BASE	0x50000000
//#define str(DATA,ADDR) (*(unsigned int*)(ADDR))=DATA
//#define ldr(DATA,ADDR) DATA=(*(unsigned int*)(ADDR))

#define CopyMMCtoMem(z,a,b,c,e)  (((bool(*)(int, unsigned int, unsigned short, unsigned int*, bool))(*((unsigned int *)0x0C004008)))(z,a,b,c,e))
