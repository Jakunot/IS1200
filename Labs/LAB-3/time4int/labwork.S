  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.global delay
.global time2string
.global hexasc
.global enable_interrupt

.data
.text

hexasc:
   andi    $t0,$a0,0xf      # ANDI mask to only take the 4 lsb
   ble     $t0,9,number     # if input ($a0) <= 9. goto "number" else continue to determine lette  
   nop                      # delay slot filler (just in case)
    
   addi    $v0,$t0,0x37     # adding 0x37 to our input coverting 10-15 to 'A'-'F'
   jr      $ra              # return
   nop                      # delay slot filler (just in case)

number:
   addi    $v0,$t0,0x30     # adding 0x30 to our input coverting 0-9 to ASCII '0'-'9'
   jr      $ra              # return
   nop                      # delay slot filler (just in case)

delay: 
    
    while:                  # will loop as long as a0 is greater than 0 
      blez $a0, end         # branch to 'end' if delay parameter (a0) is less than 0 (represents FALSE in c)
      nop
      sub $a0, $a0, 1       # else subtract 1 from the delay value 
    
      li  $t0, 0            # assign 0 to counter (int i = 0) 
      li  $t1, 3800         # assign constant 4711 to $t1 -- can be changed to adapt speed in ms
   
   for:                     # will loop/increment as long as t0 is less than t1
      bge $t0, $t1, while   # branch back to while as long as t0 is less than t1  (i < 4711)
      nop
      addi $t0, $t0, 1      # else increment t0 by 1 (adds t0 + 1 -> t0)    (i = i + 1)
      
      j for                 # jumps back to for-subroutine until t0 equal or greater than t1
      nop
   
      
   end: 
       jr $ra               #jumps back to caller
       nop
 
time2string:
                            ## PUSH to stack to protect values during time2string:
  PUSH $ra                  # PUSH register address from last jal in order to get back to main method
  PUSH $s0                  # PUSH to stack to save previous value of $s0 
  PUSH $s1                  # 
          
  move $s0, $a0             # copy address for where to save printed time 
  move $s1, $a1             # copy address for mytime from $a1 -> $s1

  andi $t0,$a1, 0x00ff
  beq $t0, 0, DING
  nop
  
                            ## extract and convert time for 10's value of min:
  andi $t0, $s1, 0xf000     # extract first 4bits from time by masking the rest  -> 1111 XXXX XXXX XXXX
  srl $a0, $t0, 12          # shift right 12 bits to derive the value        -> XXXX XXXX XXXX 1111
  jal hexasc                # convert derived hex value to asciii 
  nop
  move $t1,$v0              # copy functions returned ascii-value from $v0 to $t1
  sb $t1,0($s0)             # store converted ascii value to first byte of $s0   
  
                            ## extract and convert time for 1's value of min: 
  andi $t0, $s1,0xf00       # extract second 4bits from time by masking the rest  -> XXXX 1111 XXXX XXXX
  srl $a0, $t0,8            # shift 8bits in order to derive the value       
  jal hexasc                # convert derived hex value to ascii
  nop
  move $t1, $v0             # copy functions returned ascii-value from $v0 to $t1
  sb $t1,1($s0)             # stores ascii to byte 1 of $s0  (word-aligned memory)    
  
          
  li $t1, 0x3a              # loads ascii-value for ':'(58)
  sb $t1, 2($s0)            # stores ascii-value to byte 2 of $s0
  
                            ## extract and convert time from 10's value of second
  andi $t0, $s1, 0xf0       # extract third 4bits from time by masking the rest    -> XXXX XXXX 1111 XXXX
  srl $a0, $t0, 4           # shift 8bits in order to derive the value  
  jal hexasc                # convert derived hex value to ascii
  nop
  move $t1, $v0             # copy hexasc returned ascii-value from $v0 to $t1
  sb $t1,3($s0)             # stores ascii to byte 0 of $s0  (word-aligned memory)  
                            # extract and convert time for 1's value of second
  andi $a0, $s1, 0xf        # extract last 4bits from time by masking the rest  -> XXXX XXXX XXXX 1111   (no need to shift)       
  jal hexasc                # convert derived hex value to ascii
  nop
  move $t1, $v0             # copy functions returned ascii-value from $v0 to $t1
  sb $t1,4($s0)             # stores ascii to byte 4 of $s0  (word-aligned memory)
       
   
                            ## exit time2string 
      POP $s1              # POP previous $s1 value
      POP $s0              # POP previous $s0 value  
      POP $ra              # POP register address 
      jr  $ra               # jump back to main (back to continute from last jal in main)
      nop

DING:
    	li    $t1, 0x44             #loads immidate 78 represents D in ascii
    	sb    $t1, 0($s0)           # stores words

    	li    $t2, 0x49             #73 represents I in ascii 
    	sb    $t2, 1($s0)           
 
    	li    $t3, 0x4e             #78 represents N in ascii 
    	sb    $t3, 2($s0)           
 
    	li    $t4, 0x47             #69 represents G in ascii 
    	sb    $t4, 3($s0)           
    	
    	li    $t5, 0x0
    	sb    $t5,4($s0)
    	
    	j end
    	nop

enable_interrupt:

      ei
      jr $ra
      nop

