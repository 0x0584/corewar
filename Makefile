#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 08:07:32 by archid-           #+#    #+#              #
#    Updated: 2021/01/18 08:40:36 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include config.mk

HEADERS		:= $(shell find $(INC_DIR) -name '*.[hH]' -type f)
SRCS		:= $(shell find $(SRC_DIR) -name '*.[cC]' -type f)
OBJS		:= $(pastsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.c, $(SRCS))

NAME: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean $(FT_DIR)
	@rm -rf $(OBJS)

fclean:
	@make fclean $(FT_DIR)
	@rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
