.text
main:
addiu $sp, $sp, -20
sw $31, 16($sp)
sw $fp, 12($sp)
addi $fp, $sp, 12
# function initialized
li.s $f0, 9.43
addi $3, $fp, -4
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
lwc1 $f0, -4($fp)
li $v0, 2
mov.s $f12, $f0
syscall
.data
$string0: .asciiz "\n"
.text
li $v0, 4
la $a0, $string0
syscall
lwc1 $f0, -4($fp)
mtc1 $0, $f1
sub.s $f0, $f1, $f0
addi $3, $fp, -4
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
lwc1 $f0, -4($fp)
li $v0, 2
mov.s $f12, $f0
syscall
.data
$string1: .asciiz "\n"
.text
li $v0, 4
la $a0, $string1
syscall
lwc1 $f0, -4($fp)
li $3, 1
mtc1 $0, $f1
c.eq.s $f0, $f1
bc1t $L0
li $3, 0
$L0:
mtc1 $3, $f0
cvt.s.w $f0, $f0
addi $3, $fp, -4
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
lwc1 $f0, -4($fp)
li $v0, 2
mov.s $f12, $f0
syscall
.data
$string2: .asciiz "\n"
.text
li $v0, 4
la $a0, $string2
syscall
addi $3, $fp, -8
addi $2, $fp, -4
sw $2, 0($3)
lw $3, 0($3)
lw $3, -8($fp)
.data
$string3: .asciiz "\n"
.text
li $v0, 4
la $a0, $string3
syscall
# restoring function stack
lw $31, 16($sp)
lw $fp, 12($sp)
addiu $sp, $sp, 20
j $31


