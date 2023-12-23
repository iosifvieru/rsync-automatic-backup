# Makefile for automatic backup to external server
# Created by Tero

# Variables
CC = gcc
CFLAGS = -Wall

# Source files
SOURCE := $(wildcard *.c)

# Obj files
OBJ = $(SOURCE:.c=.o)

.DEFAULT_GOAL := main

main: $(OBJ) Header.h
	$(CC) $(CFLAGS) $^ -o $@
	
%.o: %.c Header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
	rm main