LIBFT_PATH	:= include/libft
LIBFT_LIB	:= $(LIBFT_PATH)/libft.a
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -lm -I include

SRC_COMMON	:= src/main.c
SRC			:= $(SRC_COMMON)

OBJDIR		:= obj
BINDIR		:= bin
NAME		:= miniRT
OBJ			:= $(SRC:src/%.c=$(OBJDIR)/%.o)


all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJ) $(LIBFT_LIB) | $(BINDIR)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_PATH) -lft -o $@
	@echo "Built $@"

$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_PATH)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)


# ========= Clean =========
clean:
	@$(MAKE) -s -C $(LIBFT_PATH) clean
	@rm -rf $(OBJDIR)
# 	@echo "obj/ removed"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_PATH) fclean
	@rm -rf $(BINDIR)
# 	@echo "bin/ removed"

re: fclean all


.PHONY: all valgrind clean fclean re san
miniRT valgrind clean fclean re san:
# 	@$(MAKE) T=$@ $(BINDIR)/$@