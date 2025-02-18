# CC = cc
# CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES_DIR)
# NAME = fractol
# BUILD_DIR = .build

# MINILIBX_NAME = libmlx.a
# MINILIBX_FOLDER = minilibx-linux
# MINILIBX_FLAGS =
# MINILIBS_INCLUDES_DIR =

# INCLUDES_DIR = ./includes
# INCLUDES_FILES = fractol.h vector.h
# INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# SRCS_DIR = srcs
# SRCS_FILES =			julia.c \
# 						main.c \
# 						mandelbrot.c \
# 						utils

# SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
# OBJS = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# $(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES) 
# 	@mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -c $< -o $@

# minilibx

# clean:
# 	rm -rf $(BUILD_DIR)

# fclean: clean
# 	rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re


CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES_DIR)
NAME = fractol
BUILD_DIR = .build

MINILIBX_NAME = libmlx.a
MINILIBX_FOLDER = minilibx-linux
MINILIBX_FLAGS = -L$(MINILIBX_FOLDER) -lmlx -lXext -lX11

INCLUDES_DIR = ./includes
INCLUDES_FILES = fractol.h vector.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

SRCS_DIR = srcs
SRCS_FILES = julia.c \
              main.c \
              mandelbrot.c \
              utils.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(MINILIBX_FOLDER)/$(MINILIBX_NAME)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MINILIBX_FLAGS) -lm

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES) 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(MINILIBX_FOLDER)/$(MINILIBX_NAME):
	@make -C $(MINILIBX_FOLDER)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
