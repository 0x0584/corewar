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

include config.mk

NAME		 = corewar

GLOB_HEADERS := ../$(GLOB_HEADERS) 
FT_DIR		:= ../$(FT_DIR)

LIBFT		= $(FT_DIR)/libft.a

INC_DIR		?= include
SRC_DIR		?= src
OBJ_DIR		?= .obj

EXTRA_DIR	 = .extra

CC			 = gcc
LD			 = ld

ifeq ($(DEBUG), 1)
	CFLAGS	 = -g -Og
else
	CFLAGS	 = -O3 -Werror
endif

GRN			 = \033[0;35m[o]\033[0m

CFLAGS		+= -I$(FT_DIR) -I$(GLOB_HEADERS) -I$(INC_DIR) -Wall -Wextra -Wpedantic
LDFLAGS		 = -lft -L$(FT_DIR) -lncurses

HEADERS		:= $(shell find $(INC_DIR) -name '*.[hH]' -type f)
SRCS		:= $(shell find $(SRC_DIR) -name '*.[cC]' -type f)
OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: setup $(NAME)
	@printf "$(GRN)built $(NAME).\n"

setup:
	@make -C $(FT_DIR) DEBUG=$(DEBUG)
	@echo
	@printf "\033[0;35mCC\033[0m=$(CC)\n"
	@printf "\033[0;35mCFLAGS\033[0m=$(CFLAGS)\n"
	@printf "\033[0;35mLDFLAGS\033[0m=$(LDFLAGS)\n"
	@echo

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) $(LIBFT)
	@mkdir -p $(@D)
	@printf " compiling $<..\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(FT_DIR) > /dev/null
	@rm -rf $(OBJS)

fclean:
	@make fclean -C $(FT_DIR) > /dev/null
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
	./$(NAME) foo.cor Gagnant.cor foo.cor maxidef.cor

.PHONY: all clean fclean re test check distcheck ft
