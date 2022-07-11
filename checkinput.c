/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:56:26 by obibby            #+#    #+#             */
/*   Updated: 2022/07/11 18:57:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_sorted(int *stack, int size, int n)
{
	int	i;
	int	sorted;

	i = 0;
	sorted = 1;
	while (n == 1 && i < size - 1)
	{
		if (stack[i] > stack[i + 1])
			sorted = 0;
		i++;
	}
	while (n == 2 && i < size - 1)
	{
		if (stack[i] < stack[i + 1])
			sorted = 0;
		i++;
	}
	return (sorted);
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

int	checkinput(char **argv, int size)
{
	int	i;
	int	j;
	int	ord;

	i = 0;
	j = 0;
	ord = 2;
	if (checkchars(argv, size) == 1)
		return (1);
	while (i++ < size)
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < INT_MIN)
			return (1);
		if (ord == 2 && i < size && ft_atoi(argv[i + 1]) < ft_atoi(argv[i]))
			ord = 0;
		while (j++ < size)
		{
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]) && i != j)
				return (1);
		}
		j = 0;
	}
	return (ord);
}
