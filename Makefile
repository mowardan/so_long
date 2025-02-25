NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_DIR = /usr/include/minilibx-linux
MLX_LIB = -lmlx -L$(MLX_DIR) -lXext -lX11

SRCS = flood_fill.c get_next_line.c\
       map.c get_next_line_utils.c\
       so_long.c working_on_images.c\
       destroy_func.c so_long_utils.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(MLX_LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
.SECONDARY: $(OBJS)
.PHONY: all clean fclean re
