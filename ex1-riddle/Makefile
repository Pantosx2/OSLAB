.PHONY: all clean cleanbf

all: script2 script5 script6 script8 script9 script10 script12 script13 script14 script15 script17

CC = gcc
CFLAGS = -g -O2
SHELL= /bin/bash

script2: script2.c
	$(CC) $(CFLAGS) $^ -o $@

script5: script5.c
	$(CC) $(CFLAGS) $^ -o $@

script6: script6.c
	$(CC) $(CFLAGS) $^ -o $@

script8: script8.c
	$(CC) $(CFLAGS) $^ -o $@

script9: script9.c
	$(CC) $(CFLAGS) $^ -o $@

script10: script10.c
	$(CC) $(CFLAGS) $^ -o $@

script12: script12.c
	$(CC) $(CFLAGS) $^ -o $@

script13: script13.c
	$(CC) $(CFLAGS) $^ -o $@

script14: script14.c
	$(CC) $(CFLAGS) $^ -o $@

script15: script15.c
	$(CC) -shared -o tier2.so -fPIC $^

script17: script17.c
	$(CC) -shared -o tier3.so -fPIC $^

clean: 
	rm -f script2 script5 script8 script10

cleanbf:
	rm -f bf0*