	.name "test st/sti"
	.comment "all possible calls"

	ld	%43707, r3			; load 0xaabb into r3

	st	r3,	255
	st	r3,	r5

	sti r3,	r3,	 r2
	sti r3,	r3,	 %15

	sti r3,	%15, r2
	sti r3,	%15, %15

	sti r3,	255,  r2
	sti r3,	255,  %15
