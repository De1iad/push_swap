/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:54:35 by obibby            #+#    #+#             */
/*   Updated: 2022/07/11 00:06:45 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min(int *stack, int size)
{
	int	i;
	int	x;

	i = 0;
	x = INT_MAX;
	while (i < size)
	{
		if (stack[i] < x)
			x = stack[i];
		i++;
	}
	return (x);
}

int	find_max(int *stack, int size)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (i < size)
	{
		if (stack[i] > x)
			x = stack[i];
		i++;
	}
	return (x);
}

void	stack_shift(int *stack, int size, int dir)
{
	int	i;

	i = 0;
	if (dir == 1)
	{
		while (i < size - 1)
		{
			stack[i] = stack[i + 1];
			i++;
		}
		stack[i] = '\0';
	}
	else
	{
		while (i <= size - 1)
			i++;
		while (i > 0)
		{
			stack[i] = stack[i - 1];
			i--;
		}
		stack[0] = '\0';
	}
}

void	recombine_a(int *stack1, int *stack2, t_info *info)
{
	int		i;
	char	*str;

	i = 0;
	while (stack1[0] != info->min1)
	{
		stack_rotate(stack1, info->size1, 1, "ra\n");
		info->moveno++;
	}
	while (stack2[0] != info->max2)
	{
		stack_rotate(stack2, info->size2, 1, "rb\n");
		info->moveno++;
	}
	while (info->size2 > 0)
	{
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2, info->size1);
		info->size1++;
		info->size2--;
		info->moveno++;
	}
	while (stack1[i] != info->min1)
		i++;
	if (i > (info->size1 + info->size2) / 2)
	{
		str = "rra\n";
		i = -1;
	}
	else
	{
		str = "ra\n";
		i = 1;
	}
	while (stack1[0] != info->min1)
	{
		stack_rotate(stack1, info->size1, i, str);
		info->moveno++;
	}
}

int	main(int argc, char *argv[])
{
	int	*stack1;
	int	*stack2;
	int	i;
	int	sum;

	sum = 0;
	if (argc == 1)
		return (0);
	i = checkinput(argv, argc - 1);
	if (i == 1)
		write(STDERR_FILENO, "Error\n", 6);
	if (i > 0)
		return (0);
	stack1 = ft_calloc(argc + 1, sizeof(int));
	stack2 = ft_calloc(argc + 1, sizeof(int));
	i = 0;
	while (argv[++i])
	{
		stack1[i - 1] = ft_atoi(argv[i]);
		sum += stack1[i - 1];
	}
	if (argc > 6)
		prepsort(stack1, stack2, sum / (argc - 1), argc - 1);
	else
		smallsort(stack1, stack2, argc - 1);
	//ft_printf("%d, %d, %d, %d, %d\n", stack1[0], stack1[1], stack1[2], stack1[3], stack1[4]);
	free(stack1);
	free(stack2);
	return (0);
}
