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
	.comm	i,8,8
	.comm	j,8,8
	movq $1, %r8
	movq %r8, i(%rip)
	movq $3, %r8
	movq %r8, j(%rip)
	movq i(%rip), %r8
	movq j(%rip), %r9
	cmpq %r9, %r8
jge L1
	movq i(%rip), %r8
	movq $1, %r9
	addq %r8, %r9
	movq %r9, i(%rip)
	movq i(%rip), %r8
	movq j(%rip), %r9
	cmpq %r9, %r8
jne L2
	movq j(%rip), %r8
	movq %r8, %rdi
	call printint
	jmp L3
L2:
	movq $0, %r8
	movq %r8, %rdi
	call printint
L3:
L1:
	xorl %eax, %eax
	popq %rbp
	ret
