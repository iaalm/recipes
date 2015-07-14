	ldr     r0,=0x7f008820
	ldr     r1,=0x1111
	str     r1,[r0]
	ldr     r0,=0x7f008824
	ldr	r1,[r0]
	bic	r1,#0xf
	mov	r4,r1
	orr	r1,#0xf
	ldr	r2,=5000000
loop:
	mov     r1,r4
	orr	r1,#0xf
delay:
	sub	r2,r2,#1
	cmp	r2,#0
	bne	delay
	ldr	r2,=5000000
	sub	r1,r1,#1
	str	r1,[r0]
	cmp	r1,r4
	bne	delay
	b	loop
	
