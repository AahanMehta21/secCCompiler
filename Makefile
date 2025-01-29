goal: secc

SRCS= main.c scan.c expr.c tree.c cg.c gen.c misc.c statement.c decl.c sym.c

secc: $(SRCS)
	cc -o secc -g $(SRCS)

out: out.s
	cc -o out out.s

test: secc testfiles/runtests.sh
	(cd testfiles; chmod +x runtests.sh; ./runtests.sh)

testbench: secc testfiles/runtestbench.sh
	(cd testfiles; chmod +x runtests.sh; ./runtestbench.sh)

clean:
	rm -f secc curr_output out.s out *.o

git:
	@read -p "Enter commit message: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git branch -M main; \
	git push -u origin main
