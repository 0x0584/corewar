include config.mk

all: ft
	@make  HEADERS="$(HEADERS)" FT_DIR=$(FT_DIR) -C $(VM)
	@make  HEADERS="$(HEADERS)" FT_DIR=$(FT_DIR) -C $(ASM)

ft:
	@make clean DEBUG=$(DEBUG) -C $(FT_DIR) 

re: fclean all

clean:
	@make clean -C $(FT_DIR)
	@make clean -C $(VM)
	@make clean -C $(ASM)

fclean:
	@make fclean -C $(FT_DIR)
	@make fclean -C $(VM)
	@make fclean -C $(ASM)
