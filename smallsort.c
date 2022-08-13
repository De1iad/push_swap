/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:49:26 by obibby            #+#    #+#             */
/*   Updated: 2022/08/13 11:29:56 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort3swap(int *stack1, int *stack2, t_info *d)
{
	swap(stack2, d, "");
	if (stack1[2] < stack1[0] && stack1[1] < stack1[0])
	{
		stack_rotate(d, 1, 1, "rr\n");
		if (stack1[0] > stack1[1])
			swap(stack1, d, "sa\n");
	}
	else if (stack1[2] > stack1[0] && stack1[1] > stack1[0])
	{
		swap(stack1, d, "ss\n");
		stack_rotate(d, 1, 1, "ra\n");
	}
	else if (stack1[2] > stack1[0])
		swap(stack1, d, "ss\n");
	else if (stack1[1] > stack1[0])
		stack_rotate(d, 1, -1, "rrr\n");
	return (0);
}

int	sort3(int *stack1, t_info *d)
{	
	if (stack1[2] < stack1[0] && stack1[1] < stack1[0])
	{
		stack_rotate(d, 1, 1, "ra\n");
		if (stack1[0] > stack1[1])
			swap(stack1, d, "sa\n");
	}
	else if (stack1[2] > stack1[0] && stack1[1] > stack1[0])
	{
		swap(stack1, d, "sa\n");
		stack_rotate(d, 1, 1, "ra\n");
	}
	else if (stack1[2] > stack1[0])
		swap(stack1, d, "sa\n");
	else if (stack1[1] > stack1[0])
		stack_rotate(d, 1, -1, "rra\n");
	return (0);
}

void	sortstacks5(int *stack1, int *stack2, t_info *d)
{
	push_to(stack1, stack2, d, 1);
	push_to(stack1, stack2, d, 1);
	d->min1 = find_min(stack1, d->size[1]);
	if (stack1[0] < stack1[1] && stack1[1] < stack1[2]
		&& stack2[0] < stack2[1] && stack1[0] < stack2[1])
	{
		if (stack2[1] == d->max1)
			ft_printf("sb\n");
		else if (stack2[1] > stack1[1])
			stack_rotate(d, 1, -1, "rrr\n");
		else
			stack_rotate(d, 1, 1, "rr\n");
		swap(stack2, d, "");
	}
	else if (stack2[0] < stack2[1] && (stack1[0] > stack1[1]
			|| stack1[1] > stack1[2]))
		sort3swap(stack1, stack2, d);
	else if (stack1[0] > stack1[1] || stack1[1] > stack1[2])
		sort3(stack1, d);
}

void	sort5(int *stack1, int *stack2, t_info *d)
{
	int	i;

	i = 0;
	sortstacks5(stack1, stack2, d);
	while (stack1[i] < stack2[0])
		i++;
	if (i == 1)
		stack_rotate(d, 1, 1, "ra\n");
	else if (i > 1)
		while (stack1[d->size[1] - 1] > stack2[0] && i-- > 0)
			stack_rotate(d, 1, -1, "rra\n");
	push_to(stack1, stack2, d, -1);
	sort_rem(stack1, stack2, d);
	d->min1 = find_min(stack1, d->size[1]);
	i = 0;
	while (stack1[i] != d->min1)
		i++;
	if (i > 2)
		while (stack1[0] != d->min1)
			stack_rotate(d, 1, -1, "rra\n");
	else
		while (stack1[0] != d->min1)
			stack_rotate(d, 1, 1, "ra\n");
}

int	smallsort(int *stack1, int *stack2, t_info *d)
{
	d->trial = 0;
	d->max1 = find_max(stack1, d->size[1]);
	d->min1 = find_min(stack1, d->size[1]);
	if (d->size[1] == 2)
		swap(stack1, d, "sa\n");
	else if (d->size[1] == 3)
		sort3(stack1, d);
	else if (d->size[1] == 4)
		sort4(stack1, stack2, d, 0);
	else if (d->size[1] == 5)
		sort5(stack1, stack2, d);
	return (0);
}
