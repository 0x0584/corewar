#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/02/17 16:02:03 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include config.mk

NAME		 = corewar

INC_DIR		?= include
SRC_DIR		?= src
OBJ_DIR		?= .obj

GRN			 = \033[0;35m[o]\033[0m

CFLAGS		+= -I$(INC_DIR)
LDFLAGS		+= -lncurses

SRCS		:= $(shell find $(SRC_DIR) -name '*.[cC]' -type f)
OBJS		:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

HEADERS		+= $(shell find $(INC_DIR) -name '*.[hH]' -type f)

GRN			 = \033[0;35m[o]\033[0m

none: setup

all: setup $(NAME)

setup:
	@echo
	@printf "\033[0;35mCC\033[0m      = $(CC)\n"
	@printf "\033[0;35mCFLAGS\033[0m  = $(CFLAGS)\n"
	@printf "\033[0;35mLDFLAGS\033[0m = $(LDFLAGS)\n"
	@echo

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "\n$(GRN) built $(NAME).\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) $(LIBFT)
	@mkdir -p $(@D)
	@printf " compiling $<..\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

build:
	@rm -rf $(OBJ_DIR) $(NAME)
	@make

.PHONY: all clean fclean re
