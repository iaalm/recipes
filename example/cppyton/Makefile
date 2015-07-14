parser:lexya_a.ypp lexya_a.l
	bison -d lexya_a.ypp
	lex lexya_a.l
	c++ -o parser lex.yy.c lexya_a.tab.cpp -fpermissive
clean:
	rm -f parser
	rm -f *.c
	rm -f *.cpp
	rm -f *.hpp
