secc: main.c scan.c
	cc -o secc -g main.c scan.c

clean:
	rm -f secc *.o
