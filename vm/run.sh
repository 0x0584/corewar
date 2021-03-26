#!/bin/bash
clear
make

for f in tests/*.cor
do
	echo "using $f"
	name=${f%.cor}
	echo -e " \033[0;32mA:"
	valgrind -s --log-file=${name}.valog --track-origins=yes --leak-check=full --show-leak-kinds=all\
			 ./corewar $f > ${name}.A.log
	echo -e "\033[0;0m<<<"

	echo -e "\n \033[0;31mB:"
	./corewar.exe $f > ${name}.B.log
	echo -e "\033[0;0m>>>"

	if ! diff -q ${name}.A.log ${name}.B.log &>/dev/null; then
		wdiff ${name}.B.log ${name}.A.log 2> /dev/null | colordiff
		grep -A 3 "HEAP SUMMARY" ${name}.valog
		echo -e "\033[0;33mdiff in " `diff ${name}.A.log ${name}.B.log | wc -l` " lines\033[0;0m"
		echo "======================================================="
		echo
		exit
	fi
done
