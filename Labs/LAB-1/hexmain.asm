  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Edited 2022 by J Otieno
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0, 17  # change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
hexasc: 
	
	andi $t0, $a0, 0xf 	        #takes only the 4 lsb and ignores the rest
	
	ble $t0, 9, asciiNumbers        #checks the value stored in t0 is <= 9, if this proves true jump to procedure/subroutine asciiNumbers
	
	ble $t0, 16, asciiLetters       #checks the value stored in t0 <= 15. The value stored in t0 must be > than 9 for it to jump to asciiLetters

	asciiNumbers: 
		addi $v0, $t0, 0x30 
		jr $ra
	asciiLetters:
		addi $v0, $t0, 0x37
		jr $ra
