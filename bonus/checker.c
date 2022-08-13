/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:35:58 by obibby            #+#    #+#             */
/*   Updated: 2022/08/13 13:03:54 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	init_struct(t_info *d, int max_size, int *stack1, int *stack2)
{
	d->size[0] = max_size;
	d->size[1] = 0;
	d->total = max_size;
	d->stack[0] = stack1;
	d->stack[1] = stack2;
}

void	error_exit(int *stack1, int *stack2, int id)
{
	free(stack1);
	free(stack2);
	if (id == 1)
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit(1);
	}
	exit(0);
}

void	fill_stack(char **argv, int	*stack)
{
	int	i;

	i = 0;
	while (argv[++i])
		stack[i - 1] = ft_atoi(argv[i]);
}

void	alloc_check(int *stack1, int *stack2)
{
	if (!stack1 || !stack2)
	{
		if (stack1)
			free(stack1);
		if (stack2)
			free(stack2);
		ft_printf("Memory allocation failed.\n");
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	t_info	d;
	int		*stack1;
	int		*stack2;

	if (check_input(argv, argc - 1) > 0)
		return (0);
	stack1 = ft_calloc(argc, sizeof(int));
	stack2 = ft_calloc(argc, sizeof(int));
	alloc_check(stack1, stack2);
	init_struct(&d, argc - 1, stack1, stack2);
	fill_stack(argv, stack1);
	read_commands(stack1, stack2, &d, 0);
	check_sorted(stack1, stack2, &d);
}
