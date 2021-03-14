#/bin/bash
clear
make DEPS_DIR=../include FT_DIR=../libft 

#for f in /home/foobar/Workspace/cor/Players/Assembly/*.s
for f in ../build/origin/*.cor 
do
	echo $f;
#	valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all \
	./corewar $f  #&&\
	../.extra/corewar -v 31 $f > out &&\
	wdiff vm.log out #| colordiff;
	echo "======================================================="
	echo
done

