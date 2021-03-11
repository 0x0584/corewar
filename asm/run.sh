#/bin/bash
clear
make DEPS_DIR=../include FT_DIR=../libft 

#for f in /home/foobar/Workspace/cor/Players/Assembly/*.s
for f in tests/error/*.s
do
	echo $f;
	valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./asm $f &&\
 	od -tx1 ${f%.s}.cor > $f.A.hex &&\
	./asm.exe $f && od -tx1 ${f%.s}.cor > $f.B.hex &&\
	wdiff $f.A.hex $f.B.hex | colordiff;
	echo "======================================================="
	echo
done

