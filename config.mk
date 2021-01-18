#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:47 by archid-           #+#    #+#              #
#    Updated: 2021/01/18 08:40:38 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		 = corewar
DEBUG		?= 1

FT_DIR		?= libft
INC_DIR		?= include
SRC_DIR		?= src
OBJ_DIR		?= .obj

CC			 = gcc
LD			 = ld

ifeq ($(DEBUG), 1)
	CFLAGS	 = -ggdb -Og
else
	CFLAGS	 = -O3 -Werror
endif

CFLAGS		+= -Wall -Wextra -I$(INC_DIR) -I$(FT_DIR)
LDFLAGS		 = -lft -L$(FT_DIR)

all: ft $(NAME)

ft:
	@make $(FT_DIR) DEBUG=$(DEBUG)

distcheck:
	@$(CC) -v
	@$(LD) -v
	@git --version
	@uname -a

check: all

test:
	$(NAME)
