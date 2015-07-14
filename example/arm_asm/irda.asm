
	ldr     r0,=0x7f008820
	ldr     r1,=0x1111
	str     r1,[r0]
	ldr	r1,=0xf
	ldr     r0,=0x7f008824
	ldr	r2,=0x7f008810
	ldr	r3,=0x0
	ldr	r4,=0xe
	str	r3,[r2]
	ldr	r2,=0x7f00881c
	str	r3,[r2]
	ldr	r2,=0x7f008818
loop:
	ldr	r3,[r2]
	bic	r3,r3,#0xffffff7f
	cmp	r3,#0x80
	bne	on
	str	r1,[r0]
	b	loop
on:
	str	r4,[r0]
	b	loop
	
