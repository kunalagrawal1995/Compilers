.text
main:
addiu $sp, $sp, -56
sw $31, 52($sp)
sw $fp, 48($sp)
addi $fp, $sp, 48
# function initialized
addi $3, $fp, -48
li $2, 4
sw $2, 0($3)
lw $3, 0($3)
$L1:
lw $2, -48($fp)
addi $2, $2, 4
addi $3, $fp, -44
sw $2, 0($3)
lw $3, 0($3)
$L2:
.data
$string0: .asciiz "%d"
.text
li $v0, 4
la $a0, $string0
syscall
lw $3, -44($fp)
li $v0, 1
move $a0, $3
syscall
$L0:
# restoring function stack
lw $31, 52($sp)
lw $fp, 48($sp)
addiu $sp, $sp, 56
j $31


