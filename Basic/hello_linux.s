	.file	"hello_linux.c"
	.section	.rodata
.LC0:
	.string	"Hello ubuntu!"
.LC1:
	.string	"%d\n"
	.align 8
.LC2:
	.string	"This IDE was build in 15th.Mar,2017"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$2, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 6.2.0-5ubuntu12) 6.2.0 20161005"
	.section	.note.GNU-stack,"",@progbits
