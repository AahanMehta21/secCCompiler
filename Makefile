goal: secc secc_parser1 secc_parser2

secc: main.c scan.c expr.c interpret.c tree.c
	cc -o secc -g main.c scan.c expr.c interpret.c tree.c

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

timetest: secc_parser1
	-@echo "Running timetest for secc_parser1"
	@for input in input1 input2 input3 input4 input5; do \
	  echo "Testing $$input..."; \
	  /usr/bin/time -f "Command: ./secc_parser1 $$input\nTotal Time: %E" sh -c '\
	    for i in {1..100000}; do ./secc_parser1 $$input > /dev/null; done'; \
	done

timetest2: secc_parser2
	-@echo "Running timetest2 for secc_parser2"
	@for input in input1 input2 input3 input4 input5; do \
	  echo "Testing $$input..."; \
	  /usr/bin/time -f "Command: ./secc_parser2 $$input\nTotal Time: %E" sh -c '\
	    for i in {1..100000}; do ./secc_parser2 $$input > /dev/null; done'; \
	done


clean:
	rm -f secc secc_parser1 secc_parser2 *.o

git:
	@read -p "Enter commit message: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git branch -M main; \
	git push -u origin main
