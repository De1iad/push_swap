/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:39:48 by obibby            #+#    #+#             */
/*   Updated: 2022/08/11 14:59:13 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_to_order(int *stack1, t_info *d)
{
	int	i;

	i = 0;
	d->min1 = find_min(stack1, d->size[1]);
	while (stack1[i++] != d->min1)
		continue ;
	while (stack1[0] != d->min1)
	{
		if (i < d->total / 2)
			stack_rotate(d, 1, 1, "ra\n");
		else
			stack_rotate(d, 1, -1, "rra\n");
	}
}

void	rotate_both(int dir, t_info *d)
{
	if (dir == 1)
	{
		stack_rotate(d, 1, 1, "rr\n");
		stack_rotate(d, 2, 1, "");
	}
	else if (dir == -1)
	{
		stack_rotate(d, 1, -1, "rrr\n");
		stack_rotate(d, 2, -1, "");
	}
}

void	rotate_m2(t_info *d)
{
	while (d->rotate_1 > 0 && d->rotate_2 > 0)
	{
		rotate_both(-1, d);
		d->rotate_1--;
		d->rotate_2--;
	}
	while (d->rotate_1-- > 0)
		stack_rotate(d, 1, -1, "rra\n");
	while (d->rotate_2-- > 0)
		stack_rotate(d, 2, -1, "rrb\n");
}

void	rotate_m1(t_info *d)
{
	while (d->rotate_1 > 0 && d->rotate_2 > 0)
	{
		rotate_both(1, d);
		d->rotate_1--;
		d->rotate_2--;
	}
	while (d->rotate_1-- > 0)
		stack_rotate(d, 1, 1, "ra\n");
	while (d->rotate_2-- > 0)
		stack_rotate(d, 2, 1, "rb\n");
}

void	sort_b(int *stack1, int *stack2, t_info *d)
{
	while (d->size[2] > 0)
	{
		check_path(stack1, d);
		if (d->best_method == 1)
			rotate_m1(d);
		if (d->best_method == 2)
			rotate_m2(d);
		if (d->best_method == 3)
		{
			while (d->rotate_1-- > 0)
				stack_rotate(d, 1, -1, "rra\n");
			while (d->rotate_2-- > 0)
				stack_rotate(d, 2, 1, "rb\n");
		}
		if (d->best_method == 4)
		{
			while (d->rotate_1-- > 0)
				stack_rotate(d, 1, 1, "ra\n");
			while (d->rotate_2-- > 0)
				stack_rotate(d, 2, -1, "rrb\n");
		}
		push_to(stack1, stack2, d, -1);
	}
}
