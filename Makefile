# SRC = main.c raycast.c \

# NAME = 3d

# OBJ = $(SRC:.c=.o)

# CC = cc

# CFLAGS = -Wall -Wextra

# MLX = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

# all: $(NAME)

# $(NAME): $(OBJ)
# 	@$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

# %.o: %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	@rm -rf $(OBJ)

# fclean: clean
# 	@rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

# .SECONDARY: $(OBJ)

SRC = main.c raycast.c \

NAME = 3d

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra

MLX = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX) -lm -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
