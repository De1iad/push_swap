/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:54:35 by obibby            #+#    #+#             */
/*   Updated: 2022/08/11 16:50:21 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	alloc_check(int *stack1, int *stack2, int *sorted)
{
	if (!stack1 || !stack2 || !sorted)
	{
		if (stack1)
			free(stack1);
		if (stack2)
			free(stack2);
		if (sorted)
			free(sorted);
		ft_printf("Memory allocation failed.\n");
		exit(1);
	}
}

void	use_best(t_info *d, int *stack1, int *stack2, int *sorted)
{
	int	i;
	int	x;

	i = 1;
	x = 1;
	while (i++ < 3)
		if (d->m_count[i] < d->m_count[x])
			x = i;
	if (x == 1)
		m2_plan(stack1, stack2, sorted, d);
	else
	{
		if (x == 3)
			d->trial = 4;
		m1_plan(stack1, stack2, d);
	}
}

void	begin(t_info *d, int *sorted, char *argv[], int argc)
{
	if (argc <= 6)
		smallsort(d->stack[1], d->stack[2], d);
	else
	{
		m1_plan(d->stack[1], d->stack[2], d);
		d->trial--;
		presort(d->stack[1], argv, sorted, argc - 1);
		init_vals(d, argc);
		m1_plan(d->stack[1], d->stack[2], d);
		d->trial--;
		presort(d->stack[1], argv, sorted, argc - 1);
		init_vals(d, argc);
		m2_plan(d->stack[1], d->stack[2], sorted, d);
		d->trial--;
		presort(d->stack[1], argv, sorted, argc - 1);
		init_vals(d, argc);
		use_best(d, d->stack[1], d->stack[2], sorted);
	}
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
	t_info	d;

	if (check_input(argv, argc - 1) > 0)
		return (0);
	stack1 = ft_calloc(argc, sizeof(int));
	stack2 = ft_calloc(argc, sizeof(int));
	sorted = ft_calloc(argc, sizeof(int));
	alloc_check(stack1, stack2, sorted);
	presort(stack1, argv, sorted, argc - 1);
	init_struct(&d, argc, stack1, stack2);
	begin(&d, sorted, argv, argc);
	free(stack1);
	free(stack2);
	free(sorted);
	return (0);
}
