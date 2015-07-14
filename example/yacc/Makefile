parser:lexya_a.y lexya_a.l
	bison -d lexya_a.y
	lex lexya_a.l
	cc -o parser *.c
clean:
	rm -f parser
	rm -f *.c
	rm -f *.h
