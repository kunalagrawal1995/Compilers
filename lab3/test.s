	.file	1 "test.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls

 # -G value = 0, Arch = mips1, ISA = 1
 # GNU C (Debian 4.3.5-4) version 4.3.5 (mips-linux-gnu)
 #	compiled by GNU C version 4.4.5, GMP version 4.3.2, MPFR version 3.0.0-p3.
 # warning: MPFR header version 3.0.0-p3 differs from library version 3.1.2-p3.
 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed:  test.c -meb -mllsc -mno-shared -mabi=32 -fverbose-asm
 # -fno-asynchronous-unwind-tables
 # options enabled:  -falign-loops -fargument-alias -fauto-inc-dec
 # -fbranch-count-reg -fcommon -fearly-inlining
 # -feliminate-unused-debug-types -ffunction-cse -fgcse-lm -fident -fivopts
 # -fkeep-static-consts -fleading-underscore -fmath-errno
 # -fmerge-debug-strings -fmove-loop-invariants -fpcc-struct-return
 # -fpeephole -fpic -fsched-interblock -fsched-spec
 # -fsched-stalled-insns-dep -fsigned-zeros -fsplit-ivs-in-unroller
 # -ftoplevel-reorder -ftrapping-math -ftree-cselim -ftree-loop-im
 # -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
 # -ftree-reassoc -ftree-scev-cprop -ftree-vect-loop-version -fverbose-asm
 # -fzero-initialized-in-bss -mabicalls -mcheck-zero-division
 # -mdivide-traps -mdouble-float -meb -mexplicit-relocs -mextern-sdata
 # -mfp-exceptions -mfp32 -mfused-madd -mglibc -mgp32 -mgpopt -mhard-float
 # -mllsc -mlocal-sdata -mlong32 -mno-mips16 -mno-mips3d -msplit-addresses

 # Compiler executable checksum: 85b6753ea3cb37034719bf12e6ba259f

	.rdata
	.align	2
$LC0:
	.ascii	"%d\012\000"
	.text
	.align	2
	.globl	main
	.ent	main
	.type	main, @function
main:
	.set	nomips16
	.frame	$fp,48,$31		# vars= 16, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-48	 #,,
	sw	$31,44($sp)	 #,
	sw	$fp,40($sp)	 #,
	move	$fp,$sp	 #,
	lui	$28,%hi(__gnu_local_gp)	 #,
	addiu	$28,$28,%lo(__gnu_local_gp)	 #,,
	.cprestore	16	 #
	li	$2,13			# 0xd	 # tmp205,
	sw	$2,24($fp)	 # tmp205, b
	li	$2,7			# 0x7	 # tmp206,
	sw	$2,28($fp)	 # tmp206, a
	lw	$3,28($fp)	 # tmp207, a
	lw	$2,24($fp)	 # tmp208, b
	nop
	addu	$2,$3,$2	 # D.1222, tmp207, tmp208
	addiu	$3,$2,1	 # D.1223, D.1222,
	lw	$2,28($fp)	 # tmp209, a
	nop
	mult	$3,$2	 # D.1223, tmp209
	mflo	$2	 #, D.1224
	addiu	$3,$2,1	 # D.1225, D.1224,
	lw	$2,28($fp)	 # tmp210, a
	nop
	mult	$3,$2	 # D.1225, tmp210
	mflo	$2	 #, D.1226
	addiu	$3,$2,1	 # D.1227, D.1226,
	lw	$2,28($fp)	 # tmp211, a
	nop
	mult	$3,$2	 # D.1227, tmp211
	mflo	$2	 #, D.1228
	addiu	$3,$2,1	 # D.1229, D.1228,
	lw	$2,28($fp)	 # tmp212, a
	nop
	mult	$3,$2	 # D.1229, tmp212
	mflo	$2	 #, D.1230
	addiu	$3,$2,1	 # D.1231, D.1230,
	lw	$2,28($fp)	 # tmp213, a
	nop
	mult	$3,$2	 # D.1231, tmp213
	mflo	$3	 #, D.1232
	lw	$2,28($fp)	 # tmp214, a
	nop
	mult	$2,$3	 # tmp214, D.1232
	mflo	$2	 #, tmp215
	sw	$2,28($fp)	 # tmp215, a
	lw	$2,28($fp)	 # tmp216, a
	nop
	addiu	$2,$2,1	 # tmp217, tmp216,
	sw	$2,28($fp)	 # tmp217, a
	lui	$2,%hi($LC0)	 # tmp218,
	addiu	$4,$2,%lo($LC0)	 #, tmp218,
	lw	$5,28($fp)	 #, a
	lw	$25,%call16(printf)($28)	 # tmp219,,
	nop
	jalr	$25
	nop
	 # tmp219
	lw	$28,16($fp)	 #,
	move	$sp,$fp	 #,
	lw	$31,44($sp)	 #,
	lw	$fp,40($sp)	 #,
	addiu	$sp,$sp,48	 #,,
	j	$31
	nop
	 #
	.set	macro
	.set	reorder
	.end	main
	.ident	"GCC: (Debian 4.3.5-4) 4.3.5"
