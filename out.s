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
	.comm	x,8,8
	movq $7, %r8
	movq $9, %r9
	cmpq %r9, %r8
	movq $0, %r9
	setl %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	movq $7, %r8
	movq $9, %r9
	cmpq %r9, %r8
	movq $0, %r9
	setg %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	movq $7, %r8
	movq $9, %r9
	cmpq %r9, %r8
	movq $0, %r9
	setne %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	movq $7, %r8
	movq $9, %r9
	cmpq %r9, %r8
	movq $0, %r9
	sete %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	movq $7, %r8
	movq $7, %r9
	cmpq %r9, %r8
	movq $0, %r9
	setge %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	movq $7, %r8
	movq $7, %r9
	cmpq %r9, %r8
	movq $0, %r9
	setle %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	movq $9, %r8
	movq $7, %r9
	cmpq %r9, %r8
	movq $0, %r9
	setg %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	movq $7, %r8
	movq $9, %r9
	cmpq %r9, %r8
	movq $0, %r9
	setge %r9b
	movq %r9, x(%rip)
	movq x(%rip), %r8
	movq %r8, %rdi
	call printint
	xorl %eax, %eax
	popq %rbp
	ret
