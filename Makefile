NAME	=	push_swap
NAME2	=	checker
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	main.c smallsort.c check_input.c check_path.c operations.c utils.c largesort.c method1.c method2.c
SRCS2	=	bonus/checker.c bonus/b_operations.c bonus/b_check_input.c bonus/exec_commands.c
LIBFT	=	libft/libft.a

all:	$(NAME)

$(NAME): $(SRCS) $(LIBFT)
		gcc $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

bonus: $(SRCS2) $(LIBFT)
		gcc $(CFLAGS) $(SRCS2) $(LIBFT) -o $(NAME2)

$(LIBFT):
		make -C libft/

clean:
		make clean -C libft/

fclean: clean
		rm -f $(NAME)
		rm -f $(NAME2)
		make fclean -C libft/

re: fclean all