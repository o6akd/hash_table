CFLAGS = -Wall -g -lm
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	hash_main \

all : $(PROGRAMS)

AN=a1
zip :
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi


clean :
	rm -f $(PROGRAMS) *.o





# hash problem
hash_main : hash_main.o hash_funcs.o
	$(CC) -o $@ $^

hash_main.o : hash_main.c hashmap.h
	$(CC) -c $<

hash_funcs.o : hash_funcs.c hashmap.h
	$(CC) -c $<


# Testing Targets
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

