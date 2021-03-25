DEBUG		          ?= 1
COLORED			      ?= 0

VM_DIR				   = vm
ASM_DIR				   = asm

FT_DIR		          ?= libft
FT_HEADERS	          := $(shell find $(FT_DIR) -name '*.[hH]' -type f)
LIBFT		           = $(FT_DIR)/libft.a

DEPS_DIR	          ?= include
DEPS_SRC	          := $(shell find $(DEPS_DIR) -name '*.[cC]' -type f)
DEPS		          := $(patsubst $(DEPS_DIR)/%.c,$(DEPS_DIR)/%.o,$(DEPS_SRC))

HEADERS		          := $(shell find $(DEPS_DIR) -name '*.[hH]' -type f)

CC			           = gcc
LD			           = ld

ifeq ($(DEBUG), 1)
	CFLAGS = -g -Og
else
	CFLAGS = -O3 -Werror
endif

CFLAGS		          += -Wall -Wextra -Wpedantic
CFLAGS		          += -I$(DEPS_DIR) -I$(FT_DIR)

LDFLAGS				   = -lft -L$(FT_DIR)

define relative_to
	$(shell realpath --relative-to $2 $1)
endef
