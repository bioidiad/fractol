NAME	= fractol
OS		= $(shell uname)

SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

SRC		= main.c \
		  complex.c \
		  fractol.c \
		  hooks.c \
		  math.c \
		  print.c \
		  set.c \

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

MLX		= ./minilibx/
MLX_LNK	= -L $(MLX) -l mlx -lXext -lX11

MLX_INC	= -I $(MLX)
MLX_LIB	= $(addprefix $(MLX),mlx.a)

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -l pthread

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all