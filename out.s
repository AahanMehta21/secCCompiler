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
L1:
	movq i(%rip), %r8
	movq $4, %r9
	cmpq %r9, %r8
jg L2
	movq $0, %r8
	movq %r8, j(%rip)
	movq i(%rip), %r8
	movq %r8, %rdi
	call printint
L3:
	movq j(%rip), %r8
	movq i(%rip), %r9
	cmpq %r9, %r8
jg L4
	movq j(%rip), %r8
	movq %r8, %rdi
	call printint
	movq j(%rip), %r8
	movq $1, %r9
	addq %r8, %r9
	movq %r9, j(%rip)
	jmp L3
L4:
	movq i(%rip), %r8
	movq $1, %r9
	addq %r8, %r9
	movq %r9, i(%rip)
	jmp L1
L2:
	xorl %eax, %eax
	popq %rbp
	ret
