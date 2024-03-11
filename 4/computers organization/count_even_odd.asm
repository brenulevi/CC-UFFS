		.data
vector: .word 1,3,5,7,9,11,13
len: .word 7
		.text
main:
	la a0, vector
	la t0, len
	lw a1, 0(t0)
	
	jal count_even_odd

	j end
count_even_odd:
	addi s0, zero, 0 # loop count
	addi s1, zero, 0 # even count
count_even_odd_loop_test:
	blt s0, a1, count_even_odd_loop_body
	
	add a0, zero, s1
	sub s2, a1, s1
	add a1, zero, s2
	ret
	
count_even_odd_loop_body:
	slli s3, s0, 2
	add t4, a0, s3
	lw t2, 0(t4)
	li t3, 2
	rem t3, t2, t3
	beq t2, zero, add_even
	beq t3, zero, add_even
	addi s0, s0, 1
	j count_even_odd_loop_test
add_even:
	addi s1, s1, 1
	addi s0, s0, 1
	j count_even_odd_loop_test
	
end: