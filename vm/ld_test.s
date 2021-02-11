	.name "test ld/ldi"
	.comment "all possible calls"

	ld	255,	r3				; [02 | d0] [00 ff]			[03]
	st  r3,		255

	ld	%15,	r3				; [02 | 90] [00 00 00 0f]	[03]
	st  r3,		255

	ldi	r3,		r2,		r1		; [0a | 54] [03]			[02]		[01]
	st  r1,		255

	ldi	r3,		%15,	r1		; [0a | 64] [03]			[00 0f]		[01]
	st  r1,		255

	ldi	%15,	r2,		r1		; [0a | 94] [00 0f]			[02]		[01]
	st  r1,		255

	ldi	%15,	%15,	r1		; [0a | a4] [00 0f]			[00 0f]		[01]
	st  r1,		255

	ldi	255,	r2,		r1		; [0a | d4] [00 ff]			[02]		[01]
	st  r1,		255

	ldi	255,	%15,	r1		; [0a | e4] [00 ff]			[00 0f]		[01]
	st  r1,		255

	fork %10
