all: foo

foo: foo.o bar.o
	gcc -o foo foo.o bar.o

foo.o: foo.c
	gcc -c foo.c

bar.o: bar.c
	gcc -c bar.c

clean:
	rm -f foo.o bar.o

