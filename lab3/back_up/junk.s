.text
recursion:
addiu $sp, $sp, -12
sw $31, 8($sp)
sw $fp, 4($sp)
addi $fp, $sp, 4
# function initialized
addi $3, $fp, -4
li $2, 10
sw $2, 0($3)
lw $3, 0($3)
$L1:
addi $3, $fp, 12
addi $3, $3, -400
addi $3, $3, -24
li $2, 20
sw $2, 0($3)
lw $3, 0($3)
$L2:
$L0:
# restoring function stack
lw $31, 8($sp)
lw $fp, 4($sp)
addiu $sp, $sp, 12
j $31


.text
main:
addiu $sp, $sp, -820
sw $31, 816($sp)
sw $fp, 812($sp)
addi $fp, $sp, 812
# function initialized
addi $3, $fp, -8
addi $3, $3, -400
addi $3, $3, -24
li $2, 10
sw $2, 0($3)
lw $3, 0($3)
$L3:
addi $3, $fp, -4
li $2, 1
sw $2, 0($3)
lw $3, 0($3)
$L4:
li.s $f0, 6.0
addi $3, $fp, -808
addi $3, $3, 0
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
$L5:
lw $2, -4($fp)
addi $3, $fp, -808
addi $3, $3, -4
sw $2, 0($3)
lw $3, 0($3)
$L6:
addi $3, $fp, -4
jal recursion
sw $2, 0($3)
lw $3, 0($3)
$L7:
.data
$string0: .asciiz "%d\n"
.text
li $v0, 4
la $a0, $string0
syscall
addi $3, $fp, -8
addi $3, $3, -400
addi $3, $3, -24
lw $3, 0($3)
li $v0, 1
move $a0, $3
syscall
$L2:
# restoring function stack
lw $31, 816($sp)
lw $fp, 812($sp)
addiu $sp, $sp, 820
j $31


