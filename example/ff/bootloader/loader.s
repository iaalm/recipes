	.cpu arm10tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"loader.c"
	.text
	.align	2
	.global	start_armboot
	.type	start_armboot, %function
start_armboot:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	mov	r3, #1342177280
	mov	r2, #255
	str	r2, [r3, #0]
	ldr	r3, .L6
	ldr	r3, [r3, #0]
	mov	ip, r3
	mov	r3, #0
	str	r3, [sp, #0]
	mov	r0, #1
	mov	r1, #0
	mov	r2, #10
	mov	r3, #1342177280
	blx	ip
	mov	r3, #1342177280
	ldr	r3, [r3, #0]
	cmp	r3, #255
	bne	.L2
.L3:
	b	.L3
.L2:
	ldr	r3, .L6+4
	ldr	r2, .L6+8
	str	r2, [r3, #0]
.L5:
	ldr	r3, .L6+12
	ldr	r2, .L6+12
	ldr	r2, [r2, #0]
	eor	r2, r2, #1
	str	r2, [r3, #0]
	ldr	r3, .L6+16
	str	r3, [fp, #-8]
	mov	r0, r0	@ nop
.L4:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	moveq	r3, #0
	movne	r3, #1
	and	r3, r3, #255
	ldr	r2, [fp, #-8]
	sub	r2, r2, #1
	str	r2, [fp, #-8]
	cmp	r3, #0
	bne	.L4
	b	.L5
.L7:
	.align	2
.L6:
	.word	201342984
	.word	2130741280
	.word	2236961
	.word	2130741284
	.word	1000000
	.size	start_armboot, .-start_armboot
	.ident	"GCC: (GNU) 4.7.2"
	.section	.note.GNU-stack,"",%progbits
