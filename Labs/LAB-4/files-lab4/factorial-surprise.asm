.text

	addi $a0, $0, 11	#a0 = n, where you determine the value
	addi $a1, $0, 0		#a1 outer loop counter (int i = 0)
	addi $v0, $0, 1		#return value to 1 (0! = 1)

loop: 	
	beq $a0, $a1, stop	#end if outer loop counter == n
	add $0, $0, $0		#nop
	
	addi $a1, $a1, 1	#increament outer loop counter (i++)
	mul $v0, $v0, $a1	#multiply v0 with original value
	
	addi $a3, $v0, 0	#a3 = v0 "original" value
	
	beq $0, $0, loop	#j to loop
	add $0, $0, $0		#nop
	
stop: 	
	beq $0, $0, stop	# j to stop
	add $0, $0, $0		#nop  
	
	