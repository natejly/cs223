CC = gcc
CFLAGS = -std=c17 -Wall -pedantic -g

# TO STUDENT: You may add to this file, but there must remain a target named
#   "Hookbook" that generates an executable named the same, and a target named
#   "clean" that removes all files created by the Hookbook target.

Hookbook : hookbookb.o libhookbook.o pirate_list.o pirate.o main_helpers.o #skills_list.o 
	$(CC) $(CFLAGS) -o $@ $^

# TODO: You must complete this rule to compile Hookbook, including 
#   dependencies

clean :
	$(RM) Hookbook
	$(RM) *.o