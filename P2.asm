extern printf

global main

section .text

min:
	mov rcx, rdi  ; loop counter
	dec rcx
	mov rax, [rsi]
	add rsi, 8

	; loop over rcx elements
findMinNext:
	; while (rcx > 0)
	cmp rcx, 0
	je foundNext

	; check if smaller than minimum
	mov rbx, [rsi]
	cmp rbx, rax
	jle skipValue

	; update the maximum
	mov rax, rbx

skipValue:

	; advance to the next value
	add rsi, 8
	dec rcx

	; repeat the loop
	jmp findMinNext

foundNext:

	ret

main:
	; call min() to calculate the minimum
	mov rdi, [size]
	mov rsi, list
	mov rax, 0
	call min

	; print the minimum
	mov rdi, outputFormat
	mov rsi, rax
	mov rax, 0
	call printf


;;;;;;;;;;;;;;;;;;;;;;;;
	mov r8, rsi
	mov rdi, outputFormat
	mov rsi, r8
	mov rax, 0
	call printf
;;;;;;;;;;;;;;;;;;;;;;;;


	; return 0
	mov rax, 0
	ret

section .data

	list: dq 1, 13, 29, 11, 4, 9, 18, 2
	size: dq 8
	outputFormat: db "The maximum is %d.", 0xa, 0
