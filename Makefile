OBJ = main.o linked_list.o file.o utility.o effects.o
EXEC = TurtleGraphics
CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

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

clean:
	rm -f $(EXEC) $(OBJ)

