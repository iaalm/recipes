test:prim prim_raw prim.class prim_raw.class prim.py prim_raw.py
	echo c with optimization
	time ./prim
	echo c without optimization
	time ./prim_raw
	echo java with optimization
	time java prim
	echo java without optimization
	time java prim_raw
	echo python with optimization
	time ./prim.py
	echo python without optimization
	time ./prim_raw.py

prim:prim.c
	gcc prim.c -lm -o prim
prim_raw:prim_raw.c
	gcc prim_raw.c -lm -o prim_raw
prim.class:prim.java
	javac prim.java
prim_raw.class:prim_raw.java
	javac prim_raw.java
