#ifndef _MAIN_H_
#define _MAIN_H_
void Uart_SendString(char *s);
void serial_putc(const char c);
void Uart_SendDigital(char  num);

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

typedef unsigned short      ushort;
typedef unsigned long       ulong;
typedef unsigned int        uint;

#endif

