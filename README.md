As a part of my CS250 Computer Architecture class, we had to work on making a C compiler as our final project. However most of the work like scanning, parsing, syntax, etc was already done for us, and it was highly abstracted. We ended up only writing grammar in YACC. Thus I wanted to build my own C compiler from scratch.

A self compiling C compiler following the tutorial on https://github.com/DoctorWkt/acwj and inspired from https://www.t3x.org/subc/

To run: type make, which generates the secc executable (the compiler), and then type ./secc <c_file_name>
