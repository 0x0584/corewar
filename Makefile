#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/02/10 10:28:50 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#


all: vm asm

vm:
	make -C vm 

asm:
	@echo asm

clean:
	make clean -C vm 
#	make clean -C asm

fclean:
	make fclean -C vm
#	make fclean -C asm

re: fclean all
