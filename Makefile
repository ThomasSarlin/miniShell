CC = gcc
CFLAGS = -Wall -Werror -g
SOURCES = 
TARGET = mish

all:mish

mish:parser.o mish.o echo.o cd.o external.o
	$(CC) cd.o external.o mish.o parser.o echo.c execute.h $(FLAGS) -o $(TARGET)

mish.o:mish.c mish.h 
	$(CC) $(FLAGS) -c mish.c
parser.o:parser.c parser.h
	$(CC) -c $(FLAGS) parser.c
echo.o:echo.c echo.h
	$(CC) -c $(FLAGS) echo.c
cd.o:cd.c cd.h
	$(CC) -c $(FLAGS) cd.c
external.o:external.c external.h
	$(CC) -c $(FLAGS) external.c
clear:
	rm *.o mish

valgrind:
	valgrind ./mish

