OBJ1 = main.o linked_list.o file.o utility.o effects.o
OBJ2 = main.o linked_list.o file.o simple.o effects.o
OBJ3 = main.o linked_list.o fileDebug.o utility.o effects.o

#TurtleGraphics Vanilla - Colour print, no debugging.
EXEC1 = TurtleGraphics

#TurtleGraphics Simple - LA Noire Monochromatic kinda feels (No colour print)
EXEC2 = TurtleGraphicsSimple

#TurtleGraphics Debug - Prints log entries to stdout (use with caterpie.txt for
#extra irony
EXEC3 = TurtleGraphicsDebug

CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror -g

#Make all executables
all : $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -o $(EXEC1) -lm

$(EXEC2) : $(OBJ2)
	$(CC) $(OBJ2) -o $(EXEC2) -lm

$(EXEC3) : $(OBJ3)
	$(CC) $(OBJ3) -o $(EXEC3) -lm

main.o : main.c main.h
	$(CC) -c main.c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h
	$(CC) -c linked_list.c $(CFLAGS)

file.o : file.c file.h 
	$(CC) -c file.c $(CFLAGS)

utility.o : utility.c utility.h 
	$(CC) -c utility.c $(CFLAGS)

effects.o : effects.c effects.h
	$(CC) -c effects.c $(CFLAGS)

simple.o : utility.c utility.h
	$(CC) -c utility.c -o simple.o -D SIMPLE=1 $(CFLAGS)

fileDebug.o : file.c file.h
	$(CC) -c file.c -o fileDebug.o -D DEBUG=1 $(CFLAGS)

clean:
	rm -f $(EXEC1) $(OBJ1) $(EXEC2) $(OBJ2) $(EXEC3) $(OBJ3)
