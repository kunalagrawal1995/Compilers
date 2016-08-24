	.file	1 "main_testcase.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.rdata
	.align	2
$LC1:
	.ascii	"c %d\000"
	.text
	.align	2
	.globl	main
	.ent	main
	.type	main, @function
main:
	.set	nomips16
	.frame	$fp,56,$31		# vars= 24, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$fp,48($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	16
	li	$2,1			# 0x1
	sw	$2,32($fp)
	lui	$2,%hi($LC0)
	lwc1	$f0,%lo($LC0)($2)
	nop
	swc1	$f0,24($fp)
	lwc1	$f0,32($fp)
	nop
	cvt.s.w	$f2,$f0
	li	$2,1			# 0x1
	sw	$2,44($fp)
	lwc1	$f0,24($fp)
	nop
	c.eq.s	$f2,$f0
	nop
	bc1f	$L2
	nop

	sw	$0,44($fp)
$L2:
	lw	$2,44($fp)
	nop
	sw	$2,28($fp)
	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	lw	$5,28($fp)
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($fp)
	move	$sp,$fp
	lw	$31,52($sp)
	lw	$fp,48($sp)
	addiu	$sp,$sp,56
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.rdata
	.align	2
$LC0:
	.word	1065353216
	.ident	"GCC: (Debian 4.3.5-4) 4.3.5"
