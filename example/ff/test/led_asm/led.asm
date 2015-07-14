
    ldr     r0,=0x7f008820
    ldr     r1,=0x00222221
    str     r1,[r0]
    ldr     r0,=0x7f008824
    ldr     r1,[r0]
    bic     r2,r1,#0x1
    mov	    r3,r2
    orr     r3,r3,#0x1
nn:
    str     r2,[r0]
    ldr     r4,=5000000
delay1:
    sub     r4,r4,#1
    cmp     r4,#0
    bne     delay1
    str     r3,[r0]
    ldr     r4,=5000000
delay2:
    sub     r4,r4,#1
    cmp     r4,#0
    bne     delay2
    b       nn
