#include "bigint.h"
#include "bigintprivate.h"

.Data
.align 4
oAddend1: .skip 131076
oAddend2: .skip 131076
oSum: .skip 131076

.Global BigInt_add
.text
.code 32
.align 4
BigInt_larger:
	CMP r0, r1			@ if (iLength1 > iLength2)
	MOVGE r0, r0			@ iLarger = iLength1
	MOVLT r0, r1			@ iLarger = iLength2
	BX lr				@ return iLarger

.code 32
.align 4
BigInt_add:
	PUSH {lr}
	MOV r3, #0			@ uiCarry = 0
	MOV r6, r0			@ oAddend1
	MOV r5, r1			@ oAddend2
	MOV r8, r2			@ oSum
	MOV r10, #0			@ uiSum = 0
	MOV r4, #0			@ i = 0 
	LDR r0, [r6]			@ oAddend1->iLength
	LDR r1, [r5]			@ oAddend2->iLength 
	BL BigInt_larger		@ BigInt_larger(oAddend1->iLength, oAddend2->iLength) 
	MOV r9, r0			
loop:
	CMP r4, r9			@ i < iSumLength
	BEQ end				
	MOV r10, r3			@ uiSum = uiCarry
	MOV r3, #0			@ uiCarry = 0
	ADD r4, r4, #1			@ i++ 
	LDR r7, [r6, r4, LSL #2]	@ oAddend1 -> auiDigits[i]
	ADD r10, r10, r7		@ uiSum += r4
	CMP r10, r7			@ if (uiSum < r4)
	MOVLO r3, #1			@ uiCarry = 1
	LDR r7, [r5, r4, LSL #2]	@ oAddend2 -> auiDigits[i]
	ADD r10, r10, r7		@ uiSum += r5
	CMP r10, r7			@ if (uiSum < r5)
	MOVLO r3, #1			@ uiCarry = 1

	STR r10, [r8, r4, LSL #2]	@ oSum -> auiDigits[i] = uiSum
	B loop

end:
	MOV r2, #32768			@ MAX_DIGITS
	LDR r1, =1
	CMP r3, #1 			@ if (uicarry == 1)
	BNE false			

	CMP r9, r2			@ if iSumLength == MAX_DIGITS
	MOVEQ r0, #0			@ Set r0 to false
	POPEQ {lr}			
	BXEQ lr 			@ return
	STR r1, [r8, r9, LSL #2]	@ oSum -> auiDigits[iSumLength] = 1;
	ADD r9, r9, #1			@ iSumLength++
false:
	STR r9, [r8]			@ oSum -> iLength = iSumLength
	MOV r0, #1			@ Set r0 to true
	POP {lr}			@ Pop lr
	BX lr				@ Return

.code 32
.align 4
.global main
.global BigInt_add
