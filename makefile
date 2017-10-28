all: rand.o
	gcc -o work7 rand.o

rand.o: rand.c
	gcc -c rand.c

run: all
	./work7

clean:
	rm -f work7
	rm -f *~
	rm -f *.o
	rm -f numeros

