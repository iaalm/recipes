all:compile static_link dynamical_link_local
compile:a.c b.c
	gcc a.c b.c -o compile

static_link:liba.a b.c
	gcc b.c ./liba.a -o static_link
liba.a:a.c
	gcc -c a.c -o a.o
	ar rcs liba.a a.o

dynamical_link_local:liba.so b.c
	gcc b.c ./liba.so -o dynamical_link_local

liba.so:a.c
	gcc -shared -fPIC a.c -o liba.so

clean:
	rm -f compile static_link dynamical_link_local a.o liba.a liba.so
