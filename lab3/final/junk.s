.text
just_return:
addiu $sp, $sp, -16
sw $31, 12($sp)
sw $fp, 8($sp)
addi $fp, $sp, 8
# function initialized
addi $3, $fp, -4
addi $3, $3, 0
li.s $f0, 1.0
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
$L1:
addi $3, $fp, -4
addi $3, $3, -4
li $2, 0
li $2, 0
sw $2, 0($3)
lw $3, 0($3)
$L2:
addi $3, $fp, -4
lw $2, 0($3)
sw $2, 12($fp)
lw $2, -4($3)
sw $2, 8($fp)
$L0:
# restoring function stack
lw $31, 12($sp)
lw $fp, 8($sp)
addiu $sp, $sp, 16
j $31


.text
ret_param:
addiu $sp, $sp, -8
sw $31, 4($sp)
sw $fp, 0($sp)
addi $fp, $sp, 0
# function initialized
lw $3, 8($fp)
#int
sw $3, 12($fp)
$L3:
# restoring function stack
lw $31, 4($sp)
lw $fp, 0($sp)
addiu $sp, $sp, 8
j $31


.text
recursion:
addiu $sp, $sp, -8
sw $31, 4($sp)
sw $fp, 0($sp)
addi $fp, $sp, 0
# function initialized
lw $3, 16($fp)
addi $3, $3, -400
addi $3, $3, -24
li $2, 15
li $2, 15
sw $2, 0($3)
lw $3, 0($3)
$L5:
lw $3, 12($fp)
li $2, 20
li $2, 20
sw $2, 0($3)
lw $3, 0($3)
$L6:
.data
$string0: .asciiz "f %d "
.text
li $v0, 4
la $a0, $string0
syscall
lw $3, 8($fp)
li $v0, 1
move $a0, $3
syscall
$L7:
.data
$string1: .asciiz "\n"
.text
li $v0, 4
la $a0, $string1
syscall
$L8:
.data
$string2: .asciiz "r1.r %f "
.text
li $v0, 4
la $a0, $string2
syscall
addi $3, $fp, 24
lwc1 $f0, 0($3)
li $v0, 2
mov.s $f12, $f0
syscall
$L9:
.data
$string3: .asciiz "\n"
.text
li $v0, 4
la $a0, $string3
syscall
$L10:
.data
$string4: .asciiz "r1.i %d "
.text
li $v0, 4
la $a0, $string4
syscall
addi $3, $fp, 24
lw $3, -4($3)
li $v0, 1
move $a0, $3
syscall
$L11:
.data
$string5: .asciiz "\n"
.text
li $v0, 4
la $a0, $string5
syscall
$L12:
addi $3, $fp, 24
addi $3, $3, 0
li.s $f0, 1.0
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
$L13:
addi $3, $fp, 24
addi $3, $3, -4
li $2, 0
li $2, 0
sw $2, 0($3)
lw $3, 0($3)
$L14:
li.s $f0, 1.5
lw $2, 16($fp)
addi $2, $2, -400
addi $2, $2, -24
lw $2, 0($2)
mtc1 $2, $f1
cvt.s.w $f1, $f1
add.s $f0, $f0, $f1
cvt.w.s $f0, $f0
mfc1 $3, $f0
#int
sw $3, 28($fp)
$L4:
# restoring function stack
lw $31, 4($sp)
lw $fp, 0($sp)
addiu $sp, $sp, 8
j $31


.text
main:
addiu $sp, $sp, -1624
sw $31, 1620($sp)
sw $fp, 1616($sp)
addi $fp, $sp, 1616
# function initialized
addi $3, $fp, -4
li $2, 4
sw $2, 0($3)
lw $3, 0($3)
$L16:
addi $3, $fp, -4
lwc1 $f0, -1608($fp)
cvt.w.s $f0, $f0
mfc1 $2, $f0
sw $2, 0($3)
lw $3, 0($3)
$L17:
addi $3, $fp, -1608
lw $2, -4($fp)
mtc1 $2, $f0
cvt.s.w $f0, $f0
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
$L18:
addi $3, $fp, -1608
lw $2, -4($fp)
addi $2, $2, 5
mtc1 $2, $f0
cvt.s.w $f0, $f0
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
$L19:
addi $3, $fp, -808
addi $3, $3, -400
addi $3, $3, -24
addi $2, $fp, -4
sw $2, 0($3)
lw $3, 0($3)
$L20:
addi $3, $fp, -8
addi $3, $3, -400
addi $3, $3, -24
li $2, 10
li $2, 10
sw $2, 0($3)
lw $3, 0($3)
$L21:
addi $3, $fp, -4
li $2, 10
li $2, 10
sw $2, 0($3)
lw $3, 0($3)
$L22:
addi $3, $fp, -1612
addi $3, $3, 0
li.s $f0, 0.0
swc1 $f0, 0($3)
lwc1 $f0, 0($3)
$L23:
addi $3, $fp, -1612
addi $3, $3, -4
li $2, 1
li $2, 1
sw $2, 0($3)
lw $3, 0($3)
$L24:
.data
$string6: .asciiz "a %d "
.text
li $v0, 4
la $a0, $string6
syscall
lw $3, -4($fp)
li $v0, 1
move $a0, $3
syscall
$L25:
.data
$string7: .asciiz "\n"
.text
li $v0, 4
la $a0, $string7
syscall
$L26:
.data
$string8: .asciiz "r2.r %f "
.text
li $v0, 4
la $a0, $string8
syscall
addi $3, $fp, -1612
lwc1 $f0, 0($3)
li $v0, 2
mov.s $f12, $f0
syscall
$L27:
.data
$string9: .asciiz "\n"
.text
li $v0, 4
la $a0, $string9
syscall
$L28:
.data
$string10: .asciiz "r2.i %d "
.text
li $v0, 4
la $a0, $string10
syscall
addi $3, $fp, -1612
lw $3, -4($3)
li $v0, 1
move $a0, $3
syscall
$L29:
.data
$string11: .asciiz "\n"
.text
li $v0, 4
la $a0, $string11
syscall
$L30:
.data
$string12: .asciiz "b[5][6] %d "
.text
li $v0, 4
la $a0, $string12
syscall
addi $3, $fp, -8
addi $3, $3, -400
addi $3, $3, -24
lw $3, 0($3)
li $v0, 1
move $a0, $3
syscall
$L31:
.data
$string13: .asciiz "\n"
.text
li $v0, 4
la $a0, $string13
syscall
$L32:
addi $3, $fp, -4
addi $sp, $sp, -4
sw $3, 0($sp)
li.s $f0, 1.5
# making Activation Record for recursion
# STARTING SAVE 
addi $sp, $sp, -4
sw $4, 0($sp)
addi $sp, $sp, -4
sw $3, 0($sp)
addi $sp, $sp, -4
sw $2, 0($sp)
addi $sp, $sp, -4
swc1 $f2, 0($sp)
addi $sp, $sp, -4
swc1 $f1, 0($sp)
addi $sp, $sp, -4
swc1 $f0, 0($sp)
# SAVE DONE 
addiu $sp, $sp, -4
# making Activation Record for just_return
# STARTING SAVE 
addi $sp, $sp, -4
sw $4, 0($sp)
addi $sp, $sp, -4
sw $3, 0($sp)
addi $sp, $sp, -4
sw $2, 0($sp)
addi $sp, $sp, -4
swc1 $f2, 0($sp)
addi $sp, $sp, -4
swc1 $f1, 0($sp)
addi $sp, $sp, -4
swc1 $f0, 0($sp)
# SAVE DONE 
addiu $sp, $sp, -8
jal just_return
addi $3, $sp, 4
addiu $sp, $sp, 8
# STARTING LOAD 
lwc1 $f0, 0($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
lwc1 $f2, 0($sp)
addi $sp, $sp, 4
lw $2, 0($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
lw $4, 0($sp)
addi $sp, $sp, 4
# LOAD DONE 
lw $4, 0($3)
addiu $sp, $sp, -4
sw $4, 0($sp)
lw $4, -4($3)
addiu $sp, $sp, -4
sw $4, 0($sp)
addi $3, $fp, -8
addiu $sp, $sp, -4
sw $3, 0($sp)
addi $3, $fp, -808
addi $3, $3, -400
addi $3, $3, -24
lw $3, 0($3)
addiu $sp, $sp, -4
sw $3, 0($sp)
# making Activation Record for ret_param
# STARTING SAVE 
addi $sp, $sp, -4
sw $4, 0($sp)
addi $sp, $sp, -4
sw $3, 0($sp)
addi $sp, $sp, -4
sw $2, 0($sp)
addi $sp, $sp, -4
swc1 $f2, 0($sp)
addi $sp, $sp, -4
swc1 $f1, 0($sp)
addi $sp, $sp, -4
swc1 $f0, 0($sp)
# SAVE DONE 
addiu $sp, $sp, -4
addi $3, $fp, -8
addi $3, $3, -400
addi $3, $3, -24
lw $3, 0($3)
addiu $sp, $sp, -4
sw $3, 0($sp)
jal ret_param
addi $sp, $sp, 4
lw $3, 0($sp)
addiu $sp, $sp, 4
# STARTING LOAD 
lwc1 $f0, 0($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
lwc1 $f2, 0($sp)
addi $sp, $sp, 4
lw $2, 0($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
lw $4, 0($sp)
addi $sp, $sp, 4
# LOAD DONE 
addiu $sp, $sp, -4
sw $3, 0($sp)
jal recursion
addi $sp, $sp, 20
lw $3, 0($sp)
addiu $sp, $sp, 4
mtc1 $3, $f1
cvt.s.w $f1, $f1
# STARTING LOAD 
lwc1 $f0, 0($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
lwc1 $f2, 0($sp)
addi $sp, $sp, 4
lw $2, 0($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
lw $4, 0($sp)
addi $sp, $sp, 4
# LOAD DONE 
add.s $f0, $f0, $f1
cvt.w.s $f0, $f0
mfc1 $2, $f0
lw $3, 0($sp)
addi $sp, $sp, 4
sw $2, 0($3)
lw $3, 0($3)
$L33:
.data
$string14: .asciiz "a %d "
.text
li $v0, 4
la $a0, $string14
syscall
lw $3, -4($fp)
li $v0, 1
move $a0, $3
syscall
$L34:
.data
$string15: .asciiz "\n"
.text
li $v0, 4
la $a0, $string15
syscall
$L35:
.data
$string16: .asciiz "r2.r %f "
.text
li $v0, 4
la $a0, $string16
syscall
addi $3, $fp, -1612
lwc1 $f0, 0($3)
li $v0, 2
mov.s $f12, $f0
syscall
$L36:
.data
$string17: .asciiz "\n"
.text
li $v0, 4
la $a0, $string17
syscall
$L37:
.data
$string18: .asciiz "r2.i %d "
.text
li $v0, 4
la $a0, $string18
syscall
addi $3, $fp, -1612
lw $3, -4($3)
li $v0, 1
move $a0, $3
syscall
$L38:
.data
$string19: .asciiz "\n"
.text
li $v0, 4
la $a0, $string19
syscall
$L39:
.data
$string20: .asciiz "b[5][6] %d "
.text
li $v0, 4
la $a0, $string20
syscall
addi $3, $fp, -8
addi $3, $3, -400
addi $3, $3, -24
lw $3, 0($3)
li $v0, 1
move $a0, $3
syscall
$L40:
.data
$string21: .asciiz "\n"
.text
li $v0, 4
la $a0, $string21
syscall
$L41:
addi $3, $fp, -1612
# making Activation Record for just_return
# STARTING SAVE 
addi $sp, $sp, -4
sw $4, 0($sp)
addi $sp, $sp, -4
sw $3, 0($sp)
addi $sp, $sp, -4
sw $2, 0($sp)
addi $sp, $sp, -4
swc1 $f2, 0($sp)
addi $sp, $sp, -4
swc1 $f1, 0($sp)
addi $sp, $sp, -4
swc1 $f0, 0($sp)
# SAVE DONE 
addiu $sp, $sp, -8
jal just_return
addi $2, $sp, 4
addiu $sp, $sp, 8
# STARTING LOAD 
addi $sp, $sp, 4
lwc1 $f1, 0($sp)
addi $sp, $sp, 4
lwc1 $f2, 0($sp)
addi $sp, $sp, 4
addi $sp, $sp, 4
lw $3, 0($sp)
addi $sp, $sp, 4
lw $4, 0($sp)
addi $sp, $sp, 4
# LOAD DONE 
lw $4, 0($2)
sw $4, 0($3)
lw $4, -4($2)
sw $4, -4($3)
$L42:
.data
$string22: .asciiz "r2.r %f "
.text
li $v0, 4
la $a0, $string22
syscall
addi $3, $fp, -1612
lwc1 $f0, 0($3)
li $v0, 2
mov.s $f12, $f0
syscall
$L43:
.data
$string23: .asciiz "\n"
.text
li $v0, 4
la $a0, $string23
syscall
$L44:
.data
$string24: .asciiz "r2.i %d "
.text
li $v0, 4
la $a0, $string24
syscall
addi $3, $fp, -1612
lw $3, -4($3)
li $v0, 1
move $a0, $3
syscall
$L45:
.data
$string25: .asciiz "\n"
.text
li $v0, 4
la $a0, $string25
syscall
$L15:
# restoring function stack
lw $31, 1620($sp)
lw $fp, 1616($sp)
addiu $sp, $sp, 1624
j $31


