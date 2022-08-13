/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_check_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:56:26 by obibby            #+#    #+#             */
/*   Updated: 2022/08/13 10:14:46 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rotate_both(int dir, t_info *d)
{
	if (dir == 1)
	{
		stack_rotate(d, 0, 1);
		stack_rotate(d, 1, 1);
	}
	else if (dir == -1)
	{
		stack_rotate(d, 0, -1);
		stack_rotate(d, 1, -1);
	}
}

void	check_sorted(int *stack1, int *stack2, t_info *d)
{
	int	i;

	if (d->size[0] < d->total)
	{
		ft_printf("KO\n");
		error_exit(stack1, stack2, 0);
	}
	i = 0;
	while (i < d->size[0] - 1)
	{
		if (stack1[i] > stack1[i + 1])
		{
			ft_printf("KO\n");
			error_exit(stack1, stack2, 0);
		}
		i++;
	}
	ft_printf("OK\n");
	error_exit(stack1, stack2, 0);
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
	ord = 0;
	if (s == 0)
		ord = 2;
	else if (checkchars(argv, s) == 1)
		ord = 3;
	while (ord < 2 && i++ < s)
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < INT_MIN)
			ord = 3;
		while (j++ < s)
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]) && i != j)
				ord = 3;
		j = 0;
	}
	if (ord == 3)
		write(STDERR_FILENO, "Error\n", 6);
	return (ord);
}
