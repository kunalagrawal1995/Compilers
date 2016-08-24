.text

main:
.data 
	string1: .asciiz "hey there!"
	
.text 
	li $v0, 4;
	la $a0, string1
	syscall
.data 
	string2: .asciiz "hey1 there!"
.text 
	li $v0, 4;
	la $a0, string2
	syscall
	move $a0, $10
	syscall	