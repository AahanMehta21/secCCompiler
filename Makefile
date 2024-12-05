secc: main.c scan.c expr.c interpret.c tree.c
	cc -o secc -g main.c scan.c expr.c interpret.c tree.c

clean:
	rm -f secc *.o

git:
	@read -p "Enter commit message: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git branch -M main; \
	git push -u origin main
