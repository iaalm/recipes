CC=g++
CPPFLAGS = -Isvm -Im3n
CXXFLAGS = -g -Wwrite-strings
LDFLAGS = -g
OBJECT = m3n/fun.o   m3n/m3n_main.o  m3n/m3n.o  svm/svm.o  svm/svm-train.o
	
all:learn test
learn:learn.o $(OBJECT)	 trans_train.o
test:test.o $(OBJECT)
clean:
	rm -f learn test $(OBJECT) trans_train.o learn.o test.o
