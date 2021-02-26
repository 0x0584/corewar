.name "foobar"
.comment "comment"

foo: 



bar:


buzz:

    ; read form arg left , store in arg right
	; direct argument - value
	ld  %10,   r2
	; indirect argument - reference
	ld   10,   r2

    ; using labels

    ; direct value label
	ld  %:foo, r2

    ; indirect value label
	ld  :bar,  r2



	
