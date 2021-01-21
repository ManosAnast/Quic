all: clean quic.o DeepCopy.o FileEqual.o PathFunctions.o
	gcc quic.o DeepCopy.o FileEqual.o PathFunctions.o -o quic

main.o: quic.c
	gcc -g -c quic.c

DeepCopy.o: DeepCopy.c
	gcc -g -c DeepCopy.c

FileEquality.o: FileEqual.c
	gcc -g -c FileEqual.c

PathFunctions.o: PathFunctions.c
	gcc -g -c PathFunctions.c

clean:
	rm -f quic.o DeepCopy.o FileEqual.o PathFunctions.o quic