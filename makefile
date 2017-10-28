all: rand.o
	gcc -o work7 rand.o
rand.o: rand.c
	gcc -c rand.c
run: all
	./work7
clean:
	rm *~
	rm *.o
	rm numeros

