all: clean main.o DeepCopy.o FileEquality.o PathFunctions.o
	gcc main.o DeepCopy.o FileEquality.o PathFunctions.o -o quic

main.o: main.c
	gcc -g -c main.c

DeepCopy.o: DeepCopy.c
	gcc -g -c DeepCopy.c

FileEquality.o: FileEquality.c
	gcc -g -c FileEquality.c

PathFunctions.o: PathFunctions.c
	gcc -g -c PathFunctions.c

clean:
	rm -f main.o DeepCopy.o FileEquality.o PathFunctions.o quic