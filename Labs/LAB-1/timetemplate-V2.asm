  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Edited 2022 by J Otieno
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
message: .asciiz "DING"
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)  	# get time
	addiu	$t0,$t0,1	    # increase
	andi	$t1,$t0,0xf 	# check lowest digit
	sltiu	$t2,$t1,0xa 	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	    # save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  hexasc: 
	
	and $t0, $a0, 0xf 	#takes only the 4 lsb and ignores the rest
	
	ble $t0, 9, asciiNumbers #checks the value stored in t0 is <= 9, if this proves true jump to procedure/subroutine asciiNumbers
	nop
	
	ble $t0, 16, asciiLetters #checks the value stored in t0 <= 15. The value stored in t0 must be > than 9 for it to jump to asciiLetters
	nop

	asciiNumbers: 
		addi $v0, $t0, 0x30 
		jr $ra
		nop
	asciiLetters:
		addi $v0, $t0, 0x37
		jr $ra
		nop

delay: 
	li $t1, 4711
	move $t2, $a0 # move value for a0 to t2
	
	while:
	
	blt $t2, $t0, finished # if ms > 0, which is the value stored at t2, branch to finished
	nop
	li $t0, 0  #i = 0
	sub $t2, $t2, 1 #ms = ms - 1
	
	for:
	beq $t0, $t1, while # if t0 and t1 are equal branch to while
	nop 
	addi $t0, $t0, 1  #basically i++
	j for
	nop
	
	finished:
	jr $ra
	nop 

time2string:
	
	PUSH ($s0)
	PUSH ($s1)
	PUSH ($ra)
	
	
	move $s0, $a0 #move adress of updated stored time in a0 to s0 
	move $s1, $a1 #move adress of subroutine mytime from a1 to s1
	
	andi $t0,$a1, 0x00ff
	beq $t0, 0, printding
	nop
	
	
	#since hexasc takes the 4 lsb and ignores the rest, i have to shift some bits to the right and establish  them as the 4 lsb
	
	andi $t0, $s1, 0xf000       # focus on the left 4 msb of MSB from mytime and move them to t0
	srl $a0, $t0, 12        # Shift the value to right by 12 which makes it the 4 lsb 
	jal hexasc
	nop
	sb $v0, 0($s0)      #store value at index 1
	
	andi $t0, $s1, 0xf00        #focus on the right 4 msb of the MSB from mytime and move them to t0
	srl $a0, $t0, 8         #shift the value to the right by 8 which makes it the 4 lsb
	jal hexasc
	nop
	sb $v0, 1($s0)      #store value at index 2
	
	li $t2, 0x3A        # loading the colon character 
	sb $t2, 2($s0)      #store the character at index 3
	
	andi $t0, $s1, 0xf0         #focus on left 4 lsb of the LSB from mytime and move them to t0
	srl $a0, $t0, 4         #shift the value to the right by 4 which makes it the 4 lsb
	jal hexasc
	nop
	sb $v0, 3($s0)      #store the value at index 4
	
	andi $t0, $s1, 0xf      #focus the right lsb of the LSB from mytime and move them to t0
	move $a0, $t0       #does not need to shift since it is already the 4 lsb
	jal hexasc
	nop
	sb $v0, 4($s0)      #store value at index 5
	
	li $t3, 0x00        #loading the null byte
	sb $t3, 5($s0)      #store the null byte at index 6
	
finish:
	
	POP ($ra)	
	POP ($s1)
	POP ($s0)
	
	jr $ra
	nop
	
printding:		#surprise assignment, print "DING" every minute
			    #Done in 2 different ways 

	li $t1, 0x44
	li $t2, 0x49
	li $t3, 0x4e
	li $t4, 0x47
	li $t5,0x0
		
	sb $t1,0($s0)
	sb $t2,1($s0)
	sb $t3,2($s0)
	sb $t4,3($s0)
	sb $t5,4($s0)
	
	li $a0, 10  #print new line
	li $v0, 11
	syscall
	
	

	j finish
	nop
	
