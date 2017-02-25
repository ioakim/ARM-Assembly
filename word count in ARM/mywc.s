.cpu cortex-a53
.syntax unified

.global getchar
.global printf

.data
.align 4
format: .asciz "%d, %d, %d"

.text
.code 16
.align 2
thumbfunction:
	PUSH {r4, r5, r6, r7, r8, lr}
	MOV r6, #0
	SUB r6, #1
	MOV r8, #0		@ flag
	B check

loop:
	CMP r0, #10		@ if (ch == '\n')
	IT EQ			@
	ADDEQ r5, r5, #1	@ linecount++
	CMP r0, #32		@ if ((ch != ' ')
	BNE newline		@ If not space, check new line
	BEQ flag		@ if it's space, check flag
	B check			@ check loop

char:
	ADD r4, r4, #1		@ charcount++
	MOV r8, #0		@ flag = 0
	B check

word:
	ADD r7, r7, #1		@ wordcount++
	MOV r8,  #1		@ flag = 1
	B check

newline:
	CMP r0, #10
	BNE char		@ ch != '\n'
	BEQ flag		@ if (flag == 0)

flag:
	ADD r4, r4, #1		@ charcount++
	CMP r8, #0
	BEQ word		@ if (flag == 0) wordcount++

check:
	BLX getchar		@ Get char
	CMP r6, r0 		@ ch = getchar()) != EOF)
	BNE loop		@ Go to loop if not EOF

end:
	CMP r8, #0		@ If flag == 0
	IT EQ
	ADDEQ r7, r7, #1	@ wordcount++
	blx getchar		@ Consume EOF
	MOV R1,R5
	MOV R2,R7
	MOV R3,R4
	ldr r0, =format		@ format to print
	BLX printf		@ printf
	POP {r4, r5, r6, r7, r8, lr}
	BX lr			@ return

.code 32
.align 4
.globl main
main:
	push {r6, lr}
	blx thumbfunction
	pop {r6, lr}
	bx lr
