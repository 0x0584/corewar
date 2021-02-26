# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/26 10:21:28 by archid-           #+#    #+#              #
#    Updated: 2021/02/26 10:57:47 by archid-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TEST_DIR=../.extra/tests/asm/valid
for f in `find $TEST_DIR -name '*.s' -type f`; do
	./asm $f &> tmp
	mv ${f%.*}.cor ${f%.*}.cor.mine
	../.extra/asm $f &>/dev/null
	if diff ${f%.*}.cor ${f%.*}.cor.mine; then
		echo " !!! $f"
		cat tmp
	fi
done
