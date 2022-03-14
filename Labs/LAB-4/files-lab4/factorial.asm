.text

	addi $a0, $0, 8		#a0 = n, where you determine the value
	addi $a1, $0, 0		#a1 outer loop counter (int i = 0)
	addi $v0, $0, 1		#return value to 1 (0! = 1)

loop: 	
	beq $a0, $a1, stop	#end if outer loop counter == n
	add $0, $0, $0		#nop
	
	addi $a1, $a1, 1	#increament outer loop counter (i++)
	addi $a2, $0, 1		#a2 inner loop counter (int j = 1)
	
	addi $a3, $v0, 0	#a3 = v0 "original" value

multiply: 	
	beq $a1, $a2, loop	#back to outer loop if inner loopcounter is same as outer loop counter
	add $0, $0, $0		#nop

	addi $a2, $a2, 1	#increament inner multiplier loopcounter (j++)
	
	add $v0, $v0, $a3	#increament v0 with original value

	beq $0, $0, multiply	#pseudo j to multiply
	add $0, $0, $0		#nop
	
stop: 	
	beq $0, $0, stop	#pseudo j to stop
	add $0, $0, $0		#nop  3! = 3 + 3 = 3 * 2 * 1