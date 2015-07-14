
#include "smdk6410.h"
#include "s3c6410.h"
.globl _start
_start: b reset
b	.
b	.
b	.
b	.
b	.
b	.
b	.

_start_armboot:
 .word start_armboot
 	
/*
 * the actual reset code
 */

reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0,cpsr
	bic	r0,r0,#0x1f
	orr	r0,r0,#0xd3
	msr	cpsr,r0


/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************
 */
         /*
         * we do sys-critical inits only at reboot,
         * not when booting from ram!
         */
cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
	mcr	p15, 0, r0, c1, c0, 0

	/* Peri port setup */
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
    	mcr	p15,0,r0,c15,c2,4       @ 256M(0x70000000-0x7fffffff)


	/*
	 * Go setup Memory and board specific bits prior to relocation.
	 */
	bl	lowlevel_init	/* go setup pll,mux,memory */


	stack_setup:
	 	ldr	sp, =CFG_STACK_BASE
		/*
		   测试内存是否可以正常使用
	ldr	r5, =0x50000000
	str	r5,[r5]
	ldr	r6,[r5]
	cmp	r5,r6
	beq	led
	*/

		bl	start_armboot
		/*
		   这种方法不知为什么会有问题
		ldr	pc, _start_armboot
		*/
