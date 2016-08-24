	.file	1 "test_case.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.text
	.align	2
	.globl	just_return
	.ent	just_return
	.type	just_return, @function
just_return:
	.set	nomips16
	.frame	$fp,24,$31		# vars= 8, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	0
	lui	$2,%hi($LC0)
	lwc1	$f0,%lo($LC0)($2)
	nop
	swc1	$f0,8($fp)
	sw	$0,12($fp)
	lw	$2,8($fp)
	lw	$3,12($fp)
	sw	$2,0($4)
	sw	$3,4($4)
	move	$2,$4
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	just_return
	.align	2
	.globl	ret_param
	.ent	ret_param
	.type	ret_param, @function
ret_param:
	.set	nomips16
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	sw	$4,8($fp)
	lw	$2,8($fp)
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	ret_param
	.rdata
	.align	2
$LC1:
	.ascii	"f %d \000"
	.align	2
$LC2:
	.ascii	"r1.r %f \000"
	.align	2
$LC3:
	.ascii	"r1.i %d \000"
	.text
	.align	2
	.globl	recursion
	.ent	recursion
	.type	recursion, @function
recursion:
	.set	nomips16
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	16
	sw	$4,32($fp)
	sw	$5,36($fp)
	sw	$6,40($fp)
	sw	$7,44($fp)
	lw	$2,40($fp)
	nop
	addiu	$3,$2,400
	li	$2,15			# 0xf
	sw	$2,24($3)
	lw	$3,36($fp)
	li	$2,20			# 0x14
	sw	$2,0($3)
	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	lw	$5,32($fp)
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($fp)
	lwc1	$f0,44($fp)
	nop
	cvt.d.s	$f0,$f0
	lui	$2,%hi($LC2)
	addiu	$4,$2,%lo($LC2)
	mfc1	$7,$f0
	mfc1	$6,$f1
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$3,48($fp)
	lui	$2,%hi($LC3)
	addiu	$4,$2,%lo($LC3)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($fp)
	lui	$2,%hi($LC0)
	lwc1	$f0,%lo($LC0)($2)
	nop
	swc1	$f0,44($fp)
	sw	$0,48($fp)
	lw	$2,40($fp)
	nop
	addiu	$2,$2,400
	lwc1	$f0,24($2)
	nop
	cvt.d.w	$f2,$f0
	lui	$2,%hi($LC4)
	lwc1	$f0,%lo($LC4+4)($2)
	nop
	lwc1	$f1,%lo($LC4)($2)
	nop
	add.d	$f0,$f2,$f0
	cvt.s.d	$f0,$f0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	recursion
	.rdata
	.align	2
$LC5:
	.ascii	"a %d \000"
	.align	2
$LC6:
	.ascii	"r2.r %f \000"
	.align	2
$LC7:
	.ascii	"r2.i %d \000"
	.align	2
$LC8:
	.ascii	"b[5][6] %d \000"
	.text
	.align	2
	.globl	main
	.ent	main
	.type	main, @function
main:
	.set	nomips16
	.frame	$fp,1680,$31		# vars= 1632, regs= 4/0, args= 24, gp= 8
	.mask	0xc0030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-1680
	sw	$31,1676($sp)
	sw	$fp,1672($sp)
	sw	$17,1668($sp)
	sw	$16,1664($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	24
	li	$2,4			# 0x4
	sw	$2,44($fp)
	lwc1	$f0,32($fp)
	nop
	.set	macro
	trunc.w.s $f0,$f0,$2
	.set	nomacro
	swc1	$f0,44($fp)
	lwc1	$f0,44($fp)
	nop
	cvt.s.w	$f0,$f0
	swc1	$f0,32($fp)
	lw	$2,44($fp)
	nop
	addiu	$2,$2,5
	mtc1	$2,$f0
	nop
	cvt.s.w	$f0,$f0
	swc1	$f0,32($fp)
	addiu	$2,$fp,44
	sw	$2,1272($fp)
	li	$2,10			# 0xa
	sw	$2,472($fp)
	li	$2,1			# 0x1
	sw	$2,44($fp)
	sw	$0,1648($fp)
	li	$2,1			# 0x1
	sw	$2,1652($fp)
	lw	$3,44($fp)
	lui	$2,%hi($LC5)
	addiu	$4,$2,%lo($LC5)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lwc1	$f0,1648($fp)
	nop
	cvt.d.s	$f0,$f0
	lui	$2,%hi($LC6)
	addiu	$4,$2,%lo($LC6)
	mfc1	$7,$f0
	mfc1	$6,$f1
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lw	$3,1652($fp)
	lui	$2,%hi($LC7)
	addiu	$4,$2,%lo($LC7)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lw	$3,472($fp)
	lui	$2,%hi($LC8)
	addiu	$4,$2,%lo($LC8)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lw	$2,472($fp)
	nop
	move	$4,$2
	.option	pic0
	jal	ret_param
	nop

	.option	pic2
	lw	$28,24($fp)
	move	$16,$2
	lw	$17,1272($fp)
	addiu	$2,$fp,36
	move	$4,$2
	.option	pic0
	jal	just_return
	nop

	.option	pic2
	lw	$28,24($fp)
	addiu	$3,$fp,48
	lw	$2,40($fp)
	nop
	sw	$2,16($sp)
	lw	$7,36($fp)
	move	$4,$16
	move	$5,$17
	move	$6,$3
	.option	pic0
	jal	recursion
	nop

	.option	pic2
	lw	$28,24($fp)
	.set	macro
	trunc.w.s $f0,$f0,$2
	.set	nomacro
	swc1	$f0,44($fp)
	lw	$3,44($fp)
	lui	$2,%hi($LC5)
	addiu	$4,$2,%lo($LC5)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lwc1	$f0,1648($fp)
	nop
	cvt.d.s	$f0,$f0
	lui	$2,%hi($LC6)
	addiu	$4,$2,%lo($LC6)
	mfc1	$7,$f0
	mfc1	$6,$f1
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lw	$3,1652($fp)
	lui	$2,%hi($LC7)
	addiu	$4,$2,%lo($LC7)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lw	$3,472($fp)
	lui	$2,%hi($LC8)
	addiu	$4,$2,%lo($LC8)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	addiu	$2,$fp,1648
	move	$4,$2
	.option	pic0
	jal	just_return
	nop

	.option	pic2
	lw	$28,24($fp)
	lwc1	$f0,1648($fp)
	nop
	cvt.d.s	$f0,$f0
	lui	$2,%hi($LC6)
	addiu	$4,$2,%lo($LC6)
	mfc1	$7,$f0
	mfc1	$6,$f1
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	lw	$3,1652($fp)
	lui	$2,%hi($LC7)
	addiu	$4,$2,%lo($LC7)
	move	$5,$3
	lw	$25,%call16(printf)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	li	$4,10			# 0xa
	lw	$25,%call16(putchar)($28)
	nop
	jalr	$25
	nop

	lw	$28,24($fp)
	move	$sp,$fp
	lw	$31,1676($sp)
	lw	$fp,1672($sp)
	lw	$17,1668($sp)
	lw	$16,1664($sp)
	addiu	$sp,$sp,1680
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.rdata
	.align	2
$LC0:
	.word	1065353216
	.align	3
$LC4:
	.word	1073217536
	.word	0
	.ident	"GCC: (Debian 4.3.5-4) 4.3.5"
