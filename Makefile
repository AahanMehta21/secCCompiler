goal: secc

secc: main.c scan.c expr.c interpret.c tree.c cg.c gen.c
	cc -o secc -g main.c scan.c expr.c interpret.c tree.c cg.c gen.c

secc_parser1: main.c scan.c expr.c interpret.c tree.c
	cc -o secc_parser1 -g main.c scan.c expr.c interpret.c tree.c

secc_parser2: main.c scan.c expr2.c interpret.c tree.c
	cc -o secc_parser2 -g main.c scan.c expr2.c interpret.c tree.c

test: secc_parser1
	-(./secc_parser1 input1; \
	 ./secc_parser1 input2; \
	 ./secc_parser1 input3; \
	 ./secc_parser1 input4; \
	 ./secc_parser1 input5)

test2: secc_parser2
	-(./secc_parser2 input1; \
	 ./secc_parser2 input2; \
	 ./secc_parser2 input3; \
	 ./secc_parser2 input4; \
	 ./secc_parser2 input5)

clean:
	rm -f secc secc_parser1 secc_parser2 *.o

git:
	@read -p "Enter commit message: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git branch -M main; \
	git push -u origin main
