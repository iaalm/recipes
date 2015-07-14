	org	07c00h			;where the programme to be loaded
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	call	DispStr			;display the string
	jmp	$
DispStr:
	mov	ax,BootMessage
	mov	bp,ax			;ES:BP = the address of the string
	mov	cx,16			;CX = length of the string
	mov	ax,01301h		;AH = 13,AL = 01h
	mov	bx,000ch		;PageNum is 0(BH = 0) black background red font (BL = 0Ch,highlight)
	mov	dl,0
	int	10h
	ret
BootMessage:		db	"Hello!OS world!"
times	510-($-$$)	db	0	;fill the remain space
dw	0xaa55				;flag of end
