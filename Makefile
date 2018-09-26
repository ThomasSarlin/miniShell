CC = gcc
CFLAGS = -Wall -Werror
SOURCES = 
TARGET = mish

all:mish

mish:parser.o mish.o 
	$(CC) mish.o parser.o execute.h $(FLAGS) -o $(TARGET)

mish.o:mish.c mish.h 
	$(CC) $(FLAGS) -c mish.c
parser.o:parser.c parser.h
	$(CC) -c $(FLAGS) parser.c



clear:
	rm mish.o parser.o mish
