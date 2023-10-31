		.data
vector:	 .word -3, 5, 11, 7, 4, -6
len: 	 .word 6
endline: .ascii "\n"
space:	 .ascii ", "
		.text
main:
	la a1, vector
	la t0, len
	lw a2, 0(t0)
	
	jal bubble
	
	jal print
	
	j exit
	
bubble:
	addi a2, a2, -1
	add t0, zero, a2 # i first variable -> i = size -1
f_for_test:
	bgt t0, zero, f_for_body # i > 0
	ret

f_for_body:
	add t1, zero, zero # j second variable -> j = 0
	 
s_for_test:
	blt t1, a2, s_for_body
	addi t0, t0, -1 # i--
	j f_for_test
s_for_body:
	addi t5, zero, 4
	mul t4, t1, t5
	add t2, a1, t4 # index to a[j]
	lw s0, 0(t2) # a[j]
	addi t2, t2, 4 # index to a[j+1]
	lw s1, 0(t2) # a[j+1]
	bgt s0, s1, substitute
	addi t1, t1, 1 # j++
	j s_for_test
	
substitute:
	add t3, s0, zero # int c = a[j]
	addi t2, t2, -4 # back to a[j]
	sw s1, 0(t2) # a[j] = a[j+1]
	addi t2, t2, 4
	sw t3, 0(t2) # go to a[j+1]
	j s_for_test
	
print:
	addi t0, zero, 0
	addi t1, zero, 4
	
	j p_for_test

p_for_test:
	ble t0, a2, p_for_body
	
	la t3, endline
	mv a0, t3
	addi a7, zero, 4
	ecall
	ret

p_for_body:
	mul t2, t0, t1 # index to get value
	addi a7, zero, 1
	add t2, a1, t2
	lw s0, 0(t2)
	add a0, zero, s0
	ecall
	
	add t4, a2, zero
	addi t4, t4, -1
	bgt t0, t4, no_comma
	addi a7, zero, 4
	la t3, space
	mv a0, t3
	ecall
	
no_comma:
	addi t0, t0, 1
	j p_for_test
	
exit:

	
	