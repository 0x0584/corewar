#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/02/11 14:35:35 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include config.mk

all: $(LIBFT) $(DEPS) vm asm

$(DEPS_DIR)/%.o: $(DEPS_DIR)/%.c $(LIBFT)
	@echo "compiling $<.."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(FT_HEADERS)
	@make -C $(FT_DIR) DEBUG=$(DEBUG)

vm: $(DEPS)
	@echo building $(VM_DIR)
	@make all -C $(VM_DIR) FT_DIR=$(FT_DIR) DEPS_DIR=$(DEPS_DIR) DEBUG=$(DEBUG)

asm: $(DEPS)
	@echo building $(ASM_DIR)
	@make all -C $(ASM_DIR) FT_DIR=$(FT_DIR) DEPS_DIR=$(DEPS_DIR) DEBUG=$(DEBUG)

clean:
	@make clean -C $(FT_DIR)  > /dev/null
	@make -C $(VM_DIR) clean  > /dev/null
	@make -C $(ASM_DIR) clean > /dev/null

fclean:
	@make fclean -C $(FT_DIR) > /dev/null
	@make -C $(VM_DIR)  fclean > /dev/null 
	@make -C $(ASM_DIR)	fclean > /dev/null

re: fclean all

.PHONY: all re clean fclean vm asm
