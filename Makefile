#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/02/26 10:20:48 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include config.mk

all: $(LIBFT) deps asm vm

deps: setup $(DEPS)
	@echo "compiled dependencies"

setup:
	@echo
	@printf "$(MGNT)CC$(RESET)      = $(CC)\n"
	@printf "$(MGNT)CFLAGS$(RESET)  = $(CFLAGS)\n"
	@printf "$(MGNT)LDFLAGS$(RESET) = $(LDFLAGS)\n"
	@echo

$(DEPS_DIR)/%.o: $(DEPS_DIR)/%.c $(LIBFT)
	@echo "compiling $(notdir $<).."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(FT_HEADERS)
	@$(MAKE) -C $(FT_DIR) DEBUG=$(DEBUG)

vm: $(DEPS)
#	@echo building $(VM_DIR)
	@$(MAKE) -C $(VM_DIR) FT_DIR=$(FT_DIR) DEPS_DIR=$(DEPS_DIR)

asm: $(DEPS)
#	@echo building $(ASM_DIR)
	@$(MAKE) -C $(ASM_DIR) FT_DIR=$(FT_DIR) DEPS_DIR=$(DEPS_DIR)

clean:
	@$(MAKE) clean -C $(FT_DIR)  > /dev/null
	@$(MAKE) -C $(VM_DIR) clean  > /dev/null
	@$(MAKE) -C $(ASM_DIR) clean > /dev/null

fclean:
	@$(MAKE) fclean -C $(FT_DIR) > /dev/null
	@$(MAKE) -C $(VM_DIR)  fclean > /dev/null
	@$(MAKE) -C $(ASM_DIR)	fclean > /dev/null

cleanup:
	@$(MAKE) -C $(VM_DIR)  fclean > /dev/null
	@$(MAKE) -C $(ASM_DIR)	fclean > /dev/null

re: fclean all

build: cleanup all

distcheck:
	@$(CC) -v
	@$(LD) -v
	@git --version
	@uname -a

test: all
	@$(MAKE) -C $(ASM_DIR) check
	@$(MAKE) -C $(VM_DIR) check

.PHONY: all re clean fclean vm asm distcheck check test
