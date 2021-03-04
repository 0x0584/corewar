#/bin/bash
for f in tests/valid/*.s
do
	echo $f;
	./asm $f; od -tx1 ${f%.s}.cor > $f.A.hex;
	./asm.exe $f; od -tx1 ${f%.s}.cor > $f.B.hex; 
	diff $f.A.hex $f.B.hex;
	echo "=======================================================" 
done

