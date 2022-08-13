/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:51:19 by obibby            #+#    #+#             */
/*   Updated: 2022/08/13 11:17:55 by obibby           ###   ########.fr       */
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
	x = INT_MIN;
	while (i < size)
	{
		if (stack[i] > x)
			x = stack[i];
		i++;
	}
	return (x);
}

int	sorted(int *stack, t_info *d)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i++ < d->size[1])
		if (stack[i] < stack[n])
			n = i;
	i = 0;
	while (i++ < d->size[1])
		if (stack[(n + i) % d->size[1]] > stack[(n + i + 1) % d->size[1]])
			return (1);
	return (0);
}

void	sort4(int *stack1, int *stack2, t_info *d, int i)
{
	if (stack1[0] == d->max1 && stack1[3] > stack1[2] && stack1[3] > stack1[1])
	{
		stack_rotate(d, 1, 1, "ra\n");
		if (stack1[0] > stack1[1])
			swap(stack1, d, "sa\n");
	}
	else if (stack1[3] == d->min1 && stack1[2] == d->max1)
	{
		if (stack1[0] > stack1[1])
			swap(stack1, d, "sa\n");
		stack_rotate(d, 1, -1, "rra\n");
	}
	else
	{
		push_to(stack1, stack2, d, 1);
		sort3(stack1, d);
		while (i < d->size[1] && stack1[i] < stack2[0])
			i++;
		if (i <= 2)
			while (i-- > 0)
				stack_rotate(d, 1, 1, "ra\n");
		push_to(stack1, stack2, d, -1);
	}
	rot4(stack1, d);
}

void	sort_rem(int *stack1, int *stack2, t_info *d)
{
	int	i;

	i = 0;
	while (i < d->size[1])
	{
		if (stack1[i] > stack2[0] && ((i > 0 && (stack1[i - 1] < stack2[0]
						|| stack1[i - 1] == d->max1)) || stack1[d->size[1] - 1]
				== d->max1 || stack1[d->size[1] - 1] < stack2[0]))
			break ;
		i++;
	}
	if (i == 1 || i == 2)
		while (i-- > 0)
			stack_rotate(d, 1, 1, "ra\n");
	else if (i > 2)
		stack_rotate(d, 1, -1, "rra\n");
	push_to(stack1, stack2, d, -1);
}
