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
	.file	"led.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	ldr	r3, .L3
	ldr	r2, .L3+4
	str	r2, [r3, #0]
	ldr	r3, .L3+8
	ldr	r3, [r3, #0]
	str	r3, [fp, #-8]
	ldr	r3, .L3+8
	ldr	r2, [fp, #-8]
	eor	r2, r2, #1
	str	r2, [r3, #0]
.L2:
	b	.L2
.L4:
	.align	2
.L3:
	.word	2130741280
	.word	2236961
	.word	2130741284
	.size	main, .-main
	.ident	"GCC: (GNU) 4.7.2"
	.section	.note.GNU-stack,"",%progbits
