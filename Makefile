CC = gcc
CFLAGS = -Wall -Werror -g -Wmissing-declarations -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wunreachable-code
TARGET = mish

all:mish

mish:parser.o mish.o echo.o cd.o external.o execute.o
	$(CC) cd.o external.o mish.o parser.o echo.c execute.c $(CFLAGS) -o $(TARGET)

mish.o:mish.c mish.h 
	$(CC) $(CFLAGS) -c mish.c
parser.o:parser.c parser.h
	$(CC) -c $(CFLAGS) parser.c
echo.o:echo.c echo.h
	$(CC) -c $(CFLAGS) echo.c
cd.o:cd.c
	$(CC) -c $(CFLAGS) cd.c
external.o:external.c external.h
	$(CC) -c $(CFLAGS) external.c
execute.o:execute.c execute.h
	$(CC) -c $(CFLAGS) execute.c
clear:
	rm *.o
clearAll:
	rm *.o mish
valgrind:
	valgrind ./mish

