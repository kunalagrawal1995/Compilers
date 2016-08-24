	.file	1 "test_case.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$fp,128,$31		# vars= 112, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-128
	sw	$fp,124($sp)
	move	$fp,$sp
	lw	$2,12($fp)
	nop
	sw	$2,16($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,5
	sw	$2,8($fp)
	move	$sp,$fp
	lw	$fp,124($sp)
	addiu	$sp,$sp,128
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
