Ben_Lirio: Ben_Lirio.c inventory.o
	clang -o Ben_Lirio Ben_Lirio.c inventory.o

test: test.c inventory.o
	clang -o test test.c inventory.o

inventory.o: inventory/inventory.h inventory/inventory.c
	clang -c inventory/inventory.c

clean:
	rm -f test Ben_Lirio *.o
