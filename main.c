/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:54:35 by obibby            #+#    #+#             */
/*   Updated: 2022/07/24 12:45:32 by obibby           ###   ########.fr       */
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

void	presort(int *stack, char **argv, int *sorted, int size)
{
	int	n;
	int	i;
	int	x;

	i = 0;
	while (argv[++i])
		stack[i - 1] = ft_atoi(argv[i]);
	n = 0;
	while (n < size)
	{
		x = 0;
		i = 0;
		while (i < size)
		{
			if (stack[n] > stack[i++])
				x++;
		}
		sorted[x] = stack[n++];
	}
}

int	main(int argc, char *argv[])
{
	int		*stack1;
	int		*stack2;
	int		*sorted;
	t_info	info;

	if (checkinput(argv, argc - 1) > 0)
		return (0);
	init_struct(&info, argc);
	stack1 = ft_calloc(argc, sizeof(int));
	stack2 = ft_calloc(argc, sizeof(int));
	sorted = ft_calloc(argc, sizeof(int));
	presort(stack1, argv, sorted, argc - 1);
	if (argc > 6)
		meansort(stack1, stack2, sorted, &info);
	else
		smallsort(stack1, stack2, &info);
	free(stack1);
	free(stack2);
	free(sorted);
	return (0);
}
