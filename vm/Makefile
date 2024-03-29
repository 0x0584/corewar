#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/02/26 10:23:03 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

FT_DIR		?= ../libft
DEPS_DIR	?= ../include

include config.mk

NAME		 = corewar

INC_DIR		?= include
SRC_DIR		?= src
OBJ_DIR		?= .obj

CFLAGS		+= -I$(INC_DIR)
LDFLAGS		+= -lncurses

SRCS		:= $(shell find $(SRC_DIR) -name '*.[cC]' -type f)
OBJS		:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

HEADERS		+= $(shell find $(INC_DIR) -name '*.[hH]' -type f)

ifeq ($(COLORED), 1)
    GRN		= \033[0;35m[o]\033[0m
    YLW		= \033[0;33m[o]\033[0m
    MGNT    = \033[0;35m
    RESET   = \033[0m
endif

all: setup $(NAME)

setup:
	@echo
	@printf "$(MGNT)CC$(RESET)      = $(CC)\n"
	@printf "$(MGNT)CFLAGS$(RESET)  = $(CFLAGS)\n"
	@printf "$(MGNT)LDFLAGS$(RESET) = $(LDFLAGS)\n"
	@echo

$(NAME): $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "\n$(GRN) built $(NAME).\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) $(LIBFT)
	@mkdir -p $(@D)
#	@printf " compiling $<..\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

build:
	@rm -rf $(OBJ_DIR) $(NAME)
	@make

check: all
	@./run.sh

.PHONY: all clean fclean re
