#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/01/23 16:08:24 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		 = corewar
DEBUG		?= 1

FT_DIR		?= libft

INC_DIR		?= include
SRC_DIR		?= src
OBJ_DIR		?= .obj

EXTRA_DIR	 = .extra

CC			 = gcc
LD			 = ld

ifeq ($(DEBUG), 1)
	CFLAGS	 = -ggdb -Og -DDEBUG
else
	CFLAGS	 = -O3 -Werror
endif

CFLAGS		+= -Wall -Wextra -I$(INC_DIR) -I$(FT_DIR)
LDFLAGS		 = -lft -L$(FT_DIR) -lncurses

HEADERS		:= $(shell find $(INC_DIR) -name '*.[hH]' -type f)
SRCS		:= $(shell find $(SRC_DIR) -name '*.[cC]' -type f)
OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: ft $(NAME)

ft:
	@make -C $(FT_DIR) DEBUG=$(DEBUG)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(FT_DIR)
	@rm -rf $(OBJS)

fclean:
	@make fclean -C $(FT_DIR)
	@rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

build:
	@rm -rf $(OBJ_DIR) $(NAME)
	@make

distcheck:
	@$(CC) -v
	@$(LD) -v
	@git --version
	@uname -a

check: all

test: all
	./$(NAME) foo.cor foo.cor foo.cor foo.cor

.PHONY: all clean fclean re test check distcheck ft
