CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g


Hookbook : hookbookb.o libhookbook.o pirate_list.o pirate.o main_helpers.o skills_list.o 
	$(CC) $(CFLAGS) -o $@ $^

clean :
	$(RM) Hookbook
	$(RM) *.o