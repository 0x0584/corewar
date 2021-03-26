#!/bin/bash
clear
make

for f in tests/*.s
do
	echo "using $f";
	name=${f%.s}
	echo -e "<<< \033[0;32mA:"
	valgrind -s --log-file=${name}.valog --track-origins=yes --leak-check=full --show-leak-kinds=all\
			 ./asm $f && od -tx1 ${name}.cor > ${name}.A.hex
	echo -e "\033[0;0m<<<"

	echo -e ">>> \033[0;33mB:"
	./asm.exe $f && od -tx1 ${name}.cor > ${name}.B.hex
	echo -e "\033[0;0m>>>"

	if ! diff -q ${name}.A.hex ${name}.B.hex &>/dev/null; then
		wdiff ${name}.A.hex ${name}.B.hex 2> /dev/null | colordiff > ${name}.diff
		echo -e "\033[0;31mdiff in " `diff ${name}.A.hex ${name}.B.hex | wc -l` " lines\033[0;0m"
		echo "======================================================="
		echo
	fi
done
