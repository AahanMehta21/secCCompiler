# SecC (Secondary C) Compiler
secC is my self-compiling C compiler in the making. It is written entirely in C and x84-64 Assembly.

## About the Project
As a part of my CS250 Computer Architecture class, we had to work on making a C compiler as our final project. However most of the work like scanning, parsing, syntax, etc was already done for us, and it was highly abstracted. We ended up only writing grammar in YACC. Thus I wanted to build my own C compiler from scratch.

## Features of the compiler
- Uses recursive descent parsing to parse tokens from source file and Pratt parsing to handle arithmetic operations to maintain operation precedence.
- Semantic analysis of tokens is done using Abstract Syntax Trees.
- Compiler can handle arithmetic operations, compound statements, global variables, comparision operations, nested flow control, and nested looping.
- Compiler can handle datatype requests for ```int``` and ```char```
- Testcases to test functionality of each feature is present, and testbenches are provided to test the correctness of the compiler against expected output.

### Makefile commands:
- **make**: This creates the `secc` executable, which can be used to compile a test file as follows:  
```sh
./secc testfile/test_file_name
```
This command creates the assembly file `out.s` which can be assembled using `cc` or you can run the following command which will generate the `out` executable.
```sh
make out
```
Finally run the executable to see the output.
- **make test**: This runs the `runtests.sh` script that tests the compiler's output against expected value, prints the output, and displays any difference in output if present.
- **make testbench**: This runs the `runtestbench.sh` which does the same as `make test` but without printing compiler output
- **make clean**: Removes the executable files and assembly files
-  **make git**: Streamlines the process of pushing changes to github
- **make clockskew**: runs a command to fix the clockskew error that arises during running the testbenches.

## Acknowledgements
- [Nils M Holm](https://www.t3x.org/subc/)
- [Warren Toomey](https://github.com/DoctorWkt/acwj)
