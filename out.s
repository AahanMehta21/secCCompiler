	.text
.LC0:
	.string "%d\n"
	.globl printint
printint:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movl %edi, -4(%rbp)
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	ret

	.globl main
	.type main, @function
main:
	pushq %rbp
	movq %rsp, %rbp
	.comm	numa, 8
	.comm	numb, 
