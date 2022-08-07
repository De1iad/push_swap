NAME	=	push_swap
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	main.c smallsort.c largesort.c checkinput.c operations.c utils.c newsort.c
LIBFT	=	libft/

all:	$(NAME)

$(NAME): $(SRCS)
		make re -C $(LIBFT)
		gcc $(CFLAGS) $(SRCS) ./libft/libft.a $(INCLUDE) -o $(NAME)

bonus:

	make re -C $(LIBFT)
	gcc $(CFLAGS) $(SRCS2) ./libft/libft.a $(INCLUDE) -o $(NAME)

clean:
		rm -f *.o
		make clean -C $(LIBFT)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)

re: fclean all