SHELL := /bin/bash
CC=gcc
src = $(wildcard *.c)
obj = $(src:.c=.o)

ARCH = -lpthread
all:run
mult: $(obj)
	$(CC) -o $@ $^ $(ARCH)

run:mult
	
	echo > res.txt;\
	for i in 1 2 4 8 16 32;\
	do ./mult $$i >> res.txt;\
	done;\
    python process.py;\
    exit 0;\ 
	


.ONESHELL:

.PHONY:all run clean
clean:
	rm -f $(obj) mult
