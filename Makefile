NAME	=	push_swap
NAME2	=	checker
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
OBJ_DIR	=	obj/
SRC_DIR	=	bonus/
SRCS	=	main.c smallsort.c check_input.c check_path.c operations.c utils.c largesort.c method1.c method2.c
SRCS2	=	$(wildcard $(SRC_DIR)*.c)
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)%.o)
OBJS2	=	$(SRCS2:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT	=	libft/libft.a
GREY	=	\33[1;30m
BLUE	=	\33[0;34m

all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@printf "$(GREY)Compiling $(BLUE)$(NAME)\n"
	@gcc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@printf "$(GREY)Compiling $(BLUE)$< $(GREY)> $(BLUE)$@\n"
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "$(GREY)Compiling $(BLUE)$< $(GREY)> $(BLUE)$@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS2) $(LIBFT)
	@printf "$(GREY)Compiling $(BLUE)$(NAME2)\n"
	@gcc $(CFLAGS) $(OBJS2) $(LIBFT) -o $(NAME2)

$(LIBFT):
	@printf "$(GREY)Entering $(BLUE)libft/\n"
	@make -s -C libft/

clean:
	@printf "$(GREY)Cleaning $(BLUE)$(OBJ_DIR)\n"
	@rm -fr $(OBJ_DIR)
	@printf "$(GREY)Cleaning $(BLUE)libft/\n"
	@make clean -s -C libft/

fclean: clean
	@printf "$(GREY)Deleting $(BLUE)$(NAME)\n"
	@printf "$(GREY)Deleting $(BLUE)$(NAME2)\n"
	@rm -f $(NAME)
	@rm -f $(NAME2)
	@printf "$(GREY)Deleting $(BLUE)$(LIBFT)\n"
	@make fclean -s -C libft/

re: fclean all