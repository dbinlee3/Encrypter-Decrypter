	// file header
	.arch armv6           		// armv6 architecture
	.arm		      		// arm 32-bit instruction set
        .fpu vfp	      		// floating point co-processor
	.syntax unified	      		// modern syntax

        // constant values you want to use throughout the program
        // could go below like:
        // .equ ONE, 1

	// .data // uncomment if needed

	.text 				// start of text segment

	.global encrypt			// make encrypt global for linking to
	.type	encrypt, %function	// define encrypt to be a function
	.equ	FP_OFF, 4		// fp offset distance from sp

encrypt:
	// function prologue
	push	{fp, lr}		// stack frame register save
	add	fp, sp, FP_OFF		// set frame pointer to frame base
                                                                          
	// DO NOT EDIT LINES ABOVE 

		//Swap Halves:
		LSR r2, r0, #4 // r2 = r0 >> 4; Move right by 4 bits
		LSL r3, r0, #28 // r3 = r0 << 28; Move left by 28 bits
		LSR r3, r3, #24 // r3 = r3 >> 24; Move right by 24 bits
		EOR r0, r2, r3 // r0 = r2 XOR r3;

		//XOR w/ Key:
		EOR r0, r1, r0 // r0 = r1 XOR r0;

		//Clear registers
		MOV r2, #0 // r2 = 0;
		MOV r3, #0 // r3 = 0;

	// function epilogue
	sub	sp, fp, FP_OFF		// restore stack frame top
	pop	{fp, lr}		// remove frame and restore registers
	bx	lr			// return to caller

	// function footer
	.size	encrypt, (. - encrypt)	// set size for function

	.global decrypt			// make encrypt global for linking to
	.type	decrypt, %function	// define encrypt to be a function
	.equ	FP_OFF, 4		// fp offset distance from sp

decrypt:
	// function prologue
	push	{fp, lr}		// stack frame register save
	add	fp, sp, FP_OFF		// set frame pointer to frame base

	//Reverse XOR w/ Key
	EOR r2, r1, r0 // r2 = r1 XOR r0

	//Swap halves
	LSL r3, r2, #28 // r3 = r2 << 28; Move left by 28 bits
	LSR r3, r3, #24 // r3 = r3 >> 24; Move right by 24 bits
	LSR r2, r2, #4 // r2 = r2 >> 4; Move right by 4 bits
	EOR r0, r2, r3 // r0 = r2 XOR r3

	//Clear registers
	MOV r2, #0 // r2 = 0;
	MOV r3, #0 // r3 = 0;
	
        // function epilogue
	sub	sp, fp, FP_OFF		// restore stack frame top
	pop	{fp, lr}		// remove frame and restore registers
	bx	lr			// return to caller

	// function footer
	.size	decrypt, (. - decrypt)	// set size for function

	// file footer
	.section .note.GNU-stack,"",%progbits // stack/data non-exec (linker)
.end
	Template is Arm Procedure Call Standard Compliant (for Linux)