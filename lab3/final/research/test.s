	.file	1 "test.c"
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
	.frame	$fp,24032,$31		# vars= 24016, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24032
	sw	$fp,24028($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	0
	lw	$3,16($fp)
	lw	$2,16($fp)
	nop
	addu	$2,$3,$2
	sw	$2,16($fp)
	lw	$3,16($fp)
	lw	$2,12($fp)
	nop
	addu	$4,$3,$2
	lw	$3,16($fp)
	lw	$2,12($fp)
	nop
	addu	$5,$3,$2
	lw	$3,16($fp)
	lw	$2,16($fp)
	nop
	addu	$2,$3,$2
	mult	$5,$2
	mflo	$2
	nop
	nop
	mult	$4,$2
	mflo	$2
	sll	$2,$2,3
	sll	$3,$2,4
	subu	$2,$3,$2
	addiu	$3,$fp,8
	addu	$2,$3,$2
	lw	$2,7224($2)
	nop
	sw	$2,12($fp)
	lw	$2,16($fp)
	nop
	mtc1	$2,$f0
	nop
	cvt.d.w	$f2,$f0
	lui	$2,%hi($LC0)
	lwc1	$f0,%lo($LC0+4)($2)
	nop
	lwc1	$f1,%lo($LC0)($2)
	nop
	mul.d	$f0,$f2,$f0
	.set	macro
	trunc.w.d $f2,$f0,$4
	.set	nomacro
	mfc1	$2,$f2
	nop
	sw	$2,12($fp)
	lw	$3,16($fp)
	lw	$2,8($fp)
	nop
	addu	$2,$3,$2
	sw	$2,12($fp)
	move	$sp,$fp
	lw	$fp,24028($sp)
	addiu	$sp,$sp,24032
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.rdata
	.align	3
$LC0:
	.word	1077182464
	.word	0
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
