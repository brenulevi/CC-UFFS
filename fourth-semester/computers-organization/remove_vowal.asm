		.data
word: .string "luan krzyzaniak"

		.text
main:
	la a1, word
	
	jal remove_vowal
	j end
	
remove_vowal:
	addi sp, sp, 4
	sw ra, 0(sp)
	jal get_len
	lw ra, 0(sp)
	addi sp, sp, -4
	
	li t0, 'a'
	li t1, 'e'
	li t2, 'i'
	li t3, 'o'
	li t4, 'u'
	li t5, '\0'
	
	addi a7, zero, 9
	add a0, zero, t6
	ecall
	add s2, zero, a0
	
remove_vowal_loop:
	lb s0, 0(a1)
	addi a1, a1, 1
	beq s0, t0, next
	beq s0, t1, next
	beq s0, t2, next
	beq s0, t3, next
	beq s0, t4, next
	beq s0, t5, remove_vowal_end
	
	j add_to_new
	
next:
	j remove_vowal_loop
	
add_to_new:
	sb s0, 0(a0)
	addi a0, a0, 1
	j remove_vowal_loop
	
remove_vowal_end:
	addi sp, sp, 4
	sw ra, 0(sp)
	add a0, zero, s2
	jal print
	lw ra, 0(sp)
	addi sp, sp, -4
	ret

get_len:
	li t6, 1 # string length
	
get_len_loop:
	lb s0, 0(a1)
	addi a1, a1, 1 
	beq s0, t5, get_len_end_loop
	addi t6, t6, 1
	j get_len_loop
	
get_len_end_loop:
	sub a1, a1, t6
	ret
	
print:
	addi a7, zero, 4
	ecall
	ret
end: