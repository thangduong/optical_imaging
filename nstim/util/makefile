CC      = g++
INCLUDE = -I../debug

all: CUtil.o
	ar r ../lib/util.a CUtil.o
	echo done

CUtil.o: CUtil.cpp CUtil.h
	$(CC) $(INCLUDE) -c CUtil.cpp

clean:
	-rm CUtil.o ../lib/util.a