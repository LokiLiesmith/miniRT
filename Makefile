LIBFT_PATH	:= include/libft
LIBFT_LIB	:= $(LIBFT_PATH)/libft.a
MLX_DIR		:= MLX42
LIBMLX		:= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -Wunreachable-code -Ofast -I include -I $(MLX_DIR)/include

# pick which test to build: make T=parser (defaults ot minishell)
# or you can make run-parser
T ?= miniRT
UC_T := $(shell echo $(T) | tr '[:lower:]' '[:upper:]')


# Detect OS and set appropriate flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LINK_FLAGS := -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
    LINK_FLAGS := -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
endif
SRC_MINI_RT	:= src/main.c
SRC_COMMON	:= src/parse/file_check.c src/parse/acl_parse.c src/parse/ft_atod.c \
			   src/parse/objs_parse.c src/parse/parse_utils.c src/parse/linked_list_utils.c \
			   src/utils/utils.c src/get_next_line.c src/get_next_line_utils.c  src/parse/parse_xyz_rgb.c \
			   src/parse/debug_parse.c src/mlx/mlx_hooks.c src/utils/math_utils.c src/math/vector_math.c \
			   src/render/check_intersections.c src/render/colors.c src/render/render.c src/render/sphere.c \
			   src/main.c src/render/object_manipulation.c src/render/shadows.c

# SRC_RENDER	:= src/render/render_test.c src/render/fake_parsing.c

SRC			:= $(SRC_COMMON)
SELECTED_SRC := $(SRC_$(UC_T)) $(SRC_COMMON)

OBJDIR		:= obj
BINDIR		:= bin

NAME		:= $(T)
OBJ			:= $(SELECTED_SRC:src/%.c=$(OBJDIR)/%.o)

#error if T doesn't match any SRC_*
ifeq ($(strip $(SELECTED_SRC)),)
$(error Unknown T='$(T)'. Valid options: miniRT parse math render utils)
endif

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

# ========= BUILD AND RUN ======
# ex:	make run-math
# or:	make T=math
# program expects a name of a testfile to run
run-%:
	@$(MAKE) T=$* && ./bin/$* /test_scenes/test.rt


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
	@rm -rf $(MLX_DIR)/build

re: fclean all


.PHONY: all valgrind clean fclean re san libmlx
miniRT valgrind clean fclean re san:
# 	@$(MAKE) T=$@ $(BINDIR)/$@