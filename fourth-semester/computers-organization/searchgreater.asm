		.data
vector: .word 7, -11, 15, 23, 4, 0, -3
len: .word 7		
		.text
main:
	la a0, vector
	la t0, len
	lw a1, 0(t0)
	
	jal func
	
	j end
	
func:
	li t0, 1 # i = 1
	lw s0, 0(a0) # first element as greater
loop_test:
	blt t0, a1, loop_body
	add a0, zero, s0
	ret
loop_body:
	slli t2, t0, 2 # update the address
	add a0, a0, t2 # to get A[i]
	lw t1, 0(a0)
	bgt t1, s0, swap
	addi t0, t0, 1
	j loop_test
swap:
	add s0, zero, t1
	addi t0, t0, 1
	j loop_test
	
	
end: