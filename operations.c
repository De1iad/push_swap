/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:02:07 by obibby            #+#    #+#             */
/*   Updated: 2022/07/10 22:02:47 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_rotate(int *stack, int size, int dir, char *str)
{
	int	i;
	int	temp;

	i = 0;
	ft_printf("%s", str);
	if (dir == 1)
	{
		temp = stack[0];
		while (++i <= size - 1)
			stack[i - 1] = stack[i];
		stack[size - 1] = temp;
	}
	if (dir == -1)
	{
		i = size - 1;
		temp = stack[i];
		while (i-- > 0)
			stack[i + 1] = stack[i];
		stack[0] = temp;
	}
}

int	push_to(int *src, int *dest, int ssize, int dsize)
{
	stack_shift(dest, dsize, -1);
	dest[0] = src[0];
	src[0] = 0;
	stack_shift(src, ssize, 1);
	return (0);
}

void	swap(int *stack, char *str)
{
	int	temp;

	ft_printf("%s", str);
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

void	swap_both(int *stack1, int *stack2)
{
	swap(stack1, "ss\n");
	swap(stack2, "");
}
