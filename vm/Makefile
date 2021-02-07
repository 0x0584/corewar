include config.mk

NAME		 = corewar

LDFLAGS		+= -lncurses

SRCS		:= $(shell find $(SRC_DIR) -name '*.[cC]' -type f)
OBJS		:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: sh $(NAME)

sh:
	@echo $(OBJS)
	@echo 
	@echo $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) $(LIBFT)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(NAME)

fclean: clean
	@rm -rf $(OBJ_DIR)

re: fclean all
