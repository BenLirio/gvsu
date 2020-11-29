project2: main.o inventory.o
	clang -o project2 main.o inventory.o

main.o: main.c inventory.h
	clang -c main.c

inventory.o: inventory.c inventory.h
	clang -c inventory.c

clean:
	rm -f *.o project2
