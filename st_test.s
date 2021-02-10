	.name "test st/sti"
	.comment "all possible calls"

	ld	%15, r3
	st	r3,	 255

	;; ld	1,	 r3
	;; st	r3,	 255

	;; sti r3,	r3,	 r2
	;; sti r3,	r3,	 %15

	;; sti r3,	%15, r2
	;; sti r3,	%15, %15

	;; sti r3,	255,  r2
	;; sti r3,	255,  %15
