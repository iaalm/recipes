typedef char bool;

#define U32(ADDR) (*(unsigned int*)(ADDR))

#define GPMCON		U32(0x7f008820)
#define GPMDAT		U32(0x7f008824)
#define P1MEMSTAT	U32(0x7E001000)
#define P1DIRECTCMD	U32(0x7E001008)
//#define str(DATA,ADDR) (*(unsigned int*)(ADDR))=DATA
//#define ldr(DATA,ADDR) DATA=(*(unsigned int*)(ADDR))

#define CopyMMCtoMem(z,a,b,c,e)  (((bool(*)(int, unsigned int, unsigned short, unsigned int*, bool))(*((unsigned int *)0x0C004008)))(z,a,b,c,e))
