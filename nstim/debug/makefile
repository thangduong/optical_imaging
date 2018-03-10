CC      = g++
INCLUDE = -I../debug -I../html -I../util

all: CGlobalDebug.o
	ar r ../lib/debug.a CGlobalDebug.o
	echo done

CGlobalDebug.o: CGlobalDebug.cpp CGlobalDebug.h
	$(CC) $(INCLUDE) -c CGlobalDebug.cpp

clean:
	-rm CGlobalDebug.o ../lib/debug.a