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
	.frame	$fp,32,$31		# vars= 16, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-32
	sw	$fp,28($sp)
	move	$fp,$sp
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
	lwc1	$f2,12($fp)
	mtc1	$0,$f0
	nop
	c.eq.s	$f2,$f0
	nop
	bc1t	$L2
	nop

$L6:
	lw	$2,16($fp)
	nop
	beq	$2,$0,$L2
	nop

	li	$2,2			# 0x2
	sw	$2,16($fp)
	b	$L7
	nop

$L2:
	li	$2,3			# 0x3
	sw	$2,16($fp)
$L7:
	move	$sp,$fp
	lw	$fp,28($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
