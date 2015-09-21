	.file	"matrix.c"
	.text
	.globl	MAX
	.type	MAX, @function
MAX:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	%eax, -8(%rbp)
	cmovge	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	MAX, .-MAX
	.globl	init_array
	.type	init_array, @function
init_array:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L4
.L5:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$1, (%rax)
	addl	$1, -4(%rbp)
.L4:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L5
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	init_array, .-init_array
	.globl	create_2Dmatrix
	.type	create_2Dmatrix, @function
create_2Dmatrix:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	-36(%rbp), %eax
	cltq
	movl	$8, %esi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L7
.L8:
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rbx
	movl	-40(%rbp), %eax
	cltq
	movl	$4, %esi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, (%rbx)
	addl	$1, -28(%rbp)
.L7:
	movl	-28(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L8
	movq	-24(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	create_2Dmatrix, .-create_2Dmatrix
	.section	.rodata
.LC0:
	.string	"%d "
	.text
	.globl	print_2Dmatrix
	.type	print_2Dmatrix, @function
print_2Dmatrix:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L11
.L14:
	movl	$0, -4(%rbp)
	jmp	.L12
.L13:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L12:
	movl	-4(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L13
	movl	$10, %edi
	call	putchar
	addl	$1, -8(%rbp)
.L11:
	movl	-8(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L14
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	print_2Dmatrix, .-print_2Dmatrix
	.globl	rotate_matrix
	.type	rotate_matrix, @function
rotate_matrix:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	rotate_matrix, .-rotate_matrix
	.section	.rodata
.LC1:
	.string	"MENU OPTIONS"
	.align 8
.LC2:
	.string	"1 -- Rotate matrix by 90 degree"
.LC3:
	.string	"Enter your choice"
.LC4:
	.string	"%d"
.LC5:
	.string	"Enter no of rows"
.LC6:
	.string	"Enter no of cols"
.LC7:
	.string	"\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
.L19:
	movl	$.LC1, %edi
	call	puts
	movl	$.LC2, %edi
	call	puts
	movl	$10, %edi
	call	putchar
	movl	$.LC3, %edi
	call	puts
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-20(%rbp), %eax
	cmpl	$1, %eax
	jne	.L17
	movl	$.LC5, %edi
	call	puts
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$.LC6, %edi
	call	puts
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	rotate_matrix
	movq	%rax, -8(%rbp)
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	print_2Dmatrix
	nop
.L17:
	movl	$.LC7, %edi
	call	puts
	call	getchar
	movb	%al, -21(%rbp)
	cmpb	$113, -21(%rbp)
	jne	.L19
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
