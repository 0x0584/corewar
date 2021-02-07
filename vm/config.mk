
DEBUG		?= 1

VM			 = vm
ASM			 = asm

FT_DIR		?= libft
LIBFT		?= libft.a

INC_DIR		 = $(PWD)/include
SRC_DIR		 = src
OBJ_DIR		 = .obj

HEADERS		+= $(shell find $(INC_DIR) -name '*.[hH]' -type f)

CC			?= gcc
LD			?= ld

ifeq ($(DEBUG), 1)
	CFLAGS	 = -g -Og -Wpedantic
else
	CFLAGS	 = -O3 -Werror
endif

CFLAGS		+= -Wall -Wextra -I$(INC_DIR) -I$(FT_DIR)
LDFLAGS		 = -lft -L$(FT_DIR)
