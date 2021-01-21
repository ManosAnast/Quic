all: clean quic.o DeepCopy.o FileEquality.o PathFunctions.o
	gcc quic.o DeepCopy.o FileEquality.o PathFunctions.o -o quic

main.o: quic.c
	gcc -g -c quic.c

DeepCopy.o: DeepCopy.c
	gcc -g -c DeepCopy.c

FileEquality.o: FileEquality.c
	gcc -g -c FileEquality.c

PathFunctions.o: PathFunctions.c
	gcc -g -c PathFunctions.c

clean:
	rm -f quic.o DeepCopy.o FileEquality.o PathFunctions.o quic