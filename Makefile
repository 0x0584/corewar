#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/02/14 14:56:55 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include config.mk

all: $(LIBFT) $(DEPS) asm vm

$(DEPS_DIR)/%.o: $(DEPS_DIR)/%.c $(LIBFT)
	@echo "compiling $<.."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(FT_HEADERS)
	@make -C $(FT_DIR) DEBUG=$(DEBUG)

vm: $(DEPS)
#	@echo building $(VM_DIR)
	@make -C $(VM_DIR) FT_DIR=$(FT_DIR) DEPS_DIR=$(DEPS_DIR)

asm: $(DEPS)
#	@echo building $(ASM_DIR)
	@make -C $(ASM_DIR) FT_DIR=$(FT_DIR) DEPS_DIR=$(DEPS_DIR)

clean:
	@make clean -C $(FT_DIR)  > /dev/null
	@make -C $(VM_DIR) clean  > /dev/null
	@make -C $(ASM_DIR) clean > /dev/null

fclean:
	@make fclean -C $(FT_DIR) > /dev/null
	@make -C $(VM_DIR)  fclean > /dev/null
	@make -C $(ASM_DIR)	fclean > /dev/null

cleanup:
	@make -C $(VM_DIR)  fclean > /dev/null
	@make -C $(ASM_DIR)	fclean > /dev/null

re: fclean all

build: cleanup all

distcheck:
	@$(CC) -v
	@$(LD) -v
	@git --version
	@uname -a

check: all

test: all
	./$(NAME) foo.cor Gagnant.cor foo.cor maxidef.cor

.PHONY: all re clean fclean vm asm distcheck check test
