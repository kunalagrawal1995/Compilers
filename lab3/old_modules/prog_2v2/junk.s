.text
main:
addiu $sp, $sp, -16
sw $31, 12($sp)
sw $fp, 8($sp)
addi $fp, $sp, 8
# function initialized
addi $3, $fp, -8
sw $2, 0($3)
lw $3, 0($3)
# restoring function stack
lw $31, 12($sp)
lw $fp, 8($sp)
addiu $sp, $sp, 16
j $31


