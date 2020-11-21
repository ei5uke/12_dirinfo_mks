work12: work12.o
	gcc -o work12 work12.o

work12.o: work12.c
	gcc -c work12.c

run:
	./work12

clean:
	rm -f work12
	rm -f work12.o
	echo Clean done