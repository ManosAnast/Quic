all: clean main.o DeepCopy.o FileEquality.o
	gcc main.o DeepCopy.o FileEquality.o -o quic

main.o: main.c
	gcc -g -c main.c


DeepCopy.o: DeepCopy.c
	gcc -g -c DeepCopy.c


FileEquality.o: FileEquality.c
	gcc -g -c FileEquality.c


clean:
	rm -f main.o DeepCopy.o FileEquality.o quic