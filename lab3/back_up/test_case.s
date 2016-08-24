	.file	1 "test_case.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.text
	.align	2
	.globl	recursion
	.set	nomips16
	.ent	recursion
	.type	recursion, @function
recursion:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	sw	$4,8($fp)
	sw	$5,12($fp)
	sw	$6,16($fp)
	sw	$7,20($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,400
	lw	$2,24($2)
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	recursion
	.size	recursion, .-recursion
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$fp,856,$31		# vars= 816, regs= 2/0, args= 24, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-856
	sw	$31,852($sp)
	sw	$fp,848($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	24
	li	$2,1			# 0x1
	sw	$2,32($fp)
	lui	$2,%hi($LC0)
	lwc1	$f0,%lo($LC0)($2)
	nop
	swc1	$f0,836($fp)
	lw	$2,32($fp)
	nop
	sw	$2,840($fp)
	lw	$3,32($fp)
	addiu	$2,$fp,36
	lw	$4,840($fp)
	nop
	sw	$4,16($sp)
	lw	$7,836($fp)
	move	$4,$3
	addiu	$3,$fp,32
	move	$5,$3
	move	$6,$2
	.option	pic0
	jal	recursion
	nop

	.option	pic2
	lw	$28,24($fp)
	sw	$2,32($fp)
	move	$sp,$fp
	lw	$31,852($sp)
	lw	$fp,848($sp)
	addiu	$sp,$sp,856
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.rdata
	.align	2
$LC0:
	.word	1086324736
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
