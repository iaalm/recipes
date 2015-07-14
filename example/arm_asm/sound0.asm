
	ldr     r0,=0x7f0080A0
	ldr     r1,=0x80000000
	str     r1,[r0]

	ldr     r0,=0x7f0080A8
	ldr	r1,=0x0
	str	r1,[r0]

	ldr	r2,=0x7f008830
	ldr	r3,=0x0
	str	r3,[r2]

	ldr	r2,=0x7f008834
	ldr     r0,=0x7f0080A4
	ldr	r1,=0x8000
	ldr	r4,=0x0
loop:
	ldr	r3,[r2]
	bic	r3,r3,#0xfffffffe
	cmp	r3,#1
	bne	on
	str	r1,[r0]
	b	loop
on:
	str	r4,[r0]
	b	loop
	
