/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:56:26 by obibby            #+#    #+#             */
/*   Updated: 2022/08/11 14:37:49 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_vals(t_info *d, int argc)
{
	d->size[1] = argc - 1;
	d->size[2] = 0;
	d->best_count = 0;
	d->best_method = 0;
	d->previous_val = INT_MAX;
	d->swap_count = 0;
}

void	init_struct(t_info *d, int argc, int *stack1, int *stack2)
{
	d->trial = 3;
	d->use_swap = 2;
	d->m_count[0] = 0;
	d->m_count[1] = 0;
	d->m_count[2] = 0;
	d->m_count[3] = 0;
	d->m_count[4] = 0;
	d->m_count[5] = 0;
	d->m_count[6] = 0;
	d->m_count[7] = 0;
	d->total = argc - 1;
	d->stack[1] = stack1;
	d->stack[2] = stack2;
	init_vals(d, argc);
}

int	checkchars(char **argv, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i++ < size)
	{
		while (argv[i][j])
		{
			if ((argv[i][j] == '-' && (argv[i][j + 1] < '0'
				|| argv[i][j] > '9')) || ((argv[i][j] < '0'
				|| argv[i][j] > '9') && argv[i][j] != '-'))
				return (1);
			j++;
		}
		j = 0;
	}
	return (0);
}

int	check_input(char **argv, int s)
{
	int	i;
	int	j;
	int	ord;

	i = 0;
	j = 0;
	ord = 1;
	if (s == 0)
		ord = 2;
	if (ord == 1 && checkchars(argv, s) == 1)
		ord = 3;
	while (ord != 2 && ord != 3 && i++ < s)
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < INT_MIN)
			ord = 3;
		else if (ord == 1 && i < s && ft_atoi(argv[i + 1]) < ft_atoi(argv[i]))
			ord = 0;
		while (j++ < s)
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]) && i != j)
				ord = 3;
		j = 0;
	}
	if (ord == 3)
		write(STDERR_FILENO, "Error\n", 6);
	return (ord);
}
