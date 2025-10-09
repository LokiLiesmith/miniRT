LIBFT_PATH	:= include/libft
LIBFT_LIB	:= $(LIBFT_PATH)/libft.a
MLX_DIR		:= MLX42
LIBMLX		:= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -Wunreachable-code -Ofast -I include -I $(MLX_DIR)/include

# Detect OS and set appropriate flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LINK_FLAGS := -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
    LINK_FLAGS := -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
endif

SRC_COMMON	:= src/main.c
SRC			:= $(SRC_COMMON)

OBJDIR		:= obj
BINDIR		:= bin
NAME		:= miniRT
OBJ			:= $(SRC:src/%.c=$(OBJDIR)/%.o)


all: $(BINDIR)/$(NAME)

# Clone MLX42 if not already present
$(MLX_DIR):
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

libmlx: $(MLX_DIR)
	@cmake -B $(MLX_DIR)/build $(MLX_DIR)
	@cmake --build $(MLX_DIR)/build -j4

$(BINDIR)/$(NAME): libmlx $(OBJ) $(LIBFT_LIB) | $(BINDIR)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_PATH) -lft $(LIBMLX) $(LINK_FLAGS) -o $@
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
	@rm -rf $(MLX_DIR)/build
# 	@echo "obj/ removed"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_PATH) fclean
	@rm -rf $(BINDIR)
# 	@echo "bin/ removed"

re: fclean all


.PHONY: all valgrind clean fclean re san libmlx
miniRT valgrind clean fclean re san:
# 	@$(MAKE) T=$@ $(BINDIR)/$@