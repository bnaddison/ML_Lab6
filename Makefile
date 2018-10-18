# ADDBRA001 Makefile Template

## FLAGS ==================================================================
CC=g++ -std=c++11
LIBS=-lm
## ========================================================================

ann3: ann3.o
	$(CC) ann3.o -o ann3 $(LIBS)


ann3.o: ann3.cpp
	$(CC) -c ann3.cpp

clean:
	@rm -f *.o
	@rm ann3

install:

	@mv ann3 ~/bin
