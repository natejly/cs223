CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

# TO STUDENT: You may add to this file, but there must remain a target named
#   "Hookbook" that generates an executable named the same, and a target named
#   "clean" that removes all files created by the Hookbook target.

Hookbook : hookbookb.o libhookbook.o pirate_list.o pirate.o main_helpers.o skills_list.o 
	$(CC) $(CFLAGS) -o $@ $^
test : test.o libhookbook.o pirate_list.o pirate.o main_helpers.o skills_list.o main_helpers.o
	gcc -o test test.c pirate.c pirate_list.c skills_list.c main_helpers.c libhookbook.c -Wall -std=c99


clean :
	$(RM) Hookbook
	$(RM) *.o