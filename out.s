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
	movq $1, %r8
	movq %r8, %rdi
	call printint
	movq $2, %r8
	movq %r8, %rdi
	call printint
	movq $3, %r8
	movq $3, %r9
	imulq %r8, %r9
	movq %r9, %rdi
	call printint
	xorl %eax, %eax
	popq %rbp
	ret
