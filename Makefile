# Copyright 2023 Echipa PCLP1

#compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

#define targets
TARGETS = my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c -o my_octave

clean:
	rm -f $(TARGETS)