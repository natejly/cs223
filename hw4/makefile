CC = gcc 
CFLAGS = -std=c17 -Wall -pedantic -g

all : Blotto GmapUnit

Blotto : blotto.o gmap.o string_key.o entry.o blottohelpers.o
	$(CC) $(CFLAGS) -o $@ $^

GmapUnit : gmap_unit.o gmap.o gmap_test_functions.o string_key.o
	$(CC) $(CFLAGS) -o $@ $^

clean :
	$(RM) Blotto
	$(RM) GmapUnit
	$(RM) *.o