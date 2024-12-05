secc: main.c scan.c expr.c interpret.c tree.c
	cc -o secc -g main.c scan.c expr.c interpret.c tree.c

clean:
	rm -f secc *.o
