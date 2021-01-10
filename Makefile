all: clean main.o DeepCopy.o
	gcc main.o DeepCopy.o -o quic

main.o: main.c
	gcc -g -c main.c


DeepCopy.o: main.c
	gcc -g -c DeepCopy.c

clean:
	rm -f main.o DeepCopy.o quic