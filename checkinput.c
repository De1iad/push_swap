/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:56:26 by obibby            #+#    #+#             */
/*   Updated: 2022/08/09 13:23:51 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_struct(t_info *info, int argc, int *stack1, int *stack2)
{
	info->size[1] = argc - 1;
	info->size[2] = 0;
	info->total = argc - 1;
	info->best_count = 0;
	info->best_method = 0;
	info->previous_val = INT_MAX;
	info->swap_count = 0;
	info->stack[1] = stack1;
	info->stack[2] = stack2;
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

int	checkinput(char **argv, int s)
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
