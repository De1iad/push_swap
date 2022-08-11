/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:08:03 by obibby            #+#    #+#             */
/*   Updated: 2022/08/11 14:46:36 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	find_move(t_info *d, int i)
{
	int	j;

	j = 0;
	if (d->stack[1][j] < d->stack[2][i] && d->stack[2][i] < d->max1)
		while (d->stack[1][j] < d->stack[2][i])
			j++;
	else if (d->stack[2][i] > d->min1 && d->stack[2][i] < d->max1)
	{
		if (d->stack[1][d->size[1] - 1] > d->stack[2][i])
		{
			while (d->stack[1][j] > d->stack[2][i])
				j++;
			while (d->stack[1][j] < d->stack[2][i])
				j++;
		}
	}
	else if (d->stack[2][i] > d->max1)
		while (d->stack[1][j++] != d->max1)
			continue ;
	else if (d->stack[2][i] < d->min1)
		while (d->stack[1][j] != d->min1)
			j++;
	d->ra = j;
	d->rra = (d->size[1] - j) % d->size[1];
}

void	check_reverse(t_info *d)
{
	if ((d->rra < d->ra && d->rrb < d->ra)
		|| (d->rra < d->rb && d->rrb < d->rb))
	{
		if (d->rra < d->rrb && d->rrb <= d->best_count)
		{
			d->best_method = 2;
			d->rotate_1 = (d->size[1] - d->ra) % d->size[1];
			d->rotate_2 = (d->size[2] - d->rb) % d->size[2];
			d->best_count = d->rrb;
		}
		if (d->rrb < d->rra && d->rra <= d->best_count)
		{
			d->best_method = 2;
			d->rotate_1 = (d->size[1] - d->ra) % d->size[1];
			d->rotate_2 = (d->size[2] - d->rb) % d->size[2];
			d->best_count = d->rra;
		}
	}
}

void	check_forward(t_info *d)
{
	if ((d->ra <= d->rra && d->rb <= d->rra)
		|| (d->ra <= d->rrb && d->rb <= d->rrb))
	{
		if (d->ra < d->rb && d->rb <= d->best_count)
		{
			d->best_method = 1;
			d->rotate_1 = d->ra;
			d->rotate_2 = d->rb;
			d->best_count = d->rb;
		}
		else if (d->rb < d->ra && d->ra <= d->best_count)
		{
			d->best_method = 1;
			d->rotate_1 = d->ra;
			d->rotate_2 = d->rb;
			d->best_count = d->ra;
		}
	}
}

void	check_mix(t_info *d)
{
	if (d->rb + d->rra < d->best_count)
	{
		d->best_method = 3;
		d->rotate_1 = (d->size[1] - d->ra) % d->size[1];
		d->rotate_2 = d->rb;
		d->best_count = d->rb + d->rra;
	}
	if (d->ra + d->rrb < d->best_count)
	{
		d->best_method = 4;
		d->rotate_1 = d->ra;
		d->rotate_2 = (d->size[2] - d->rb) % d->size[2];
		d->best_count = d->ra + d->rrb;
	}
}

void	check_path(int *stack1, t_info *d)
{
	int	i;

	i = -1;
	d->best_count = d->total * 2;
	d->min1 = find_min(stack1, d->size[1]);
	d->max1 = find_max(stack1, d->size[1]);
	while (++i < d->size[2])
	{
		find_move(d, i);
		d->rb = i;
		d->rrb = (d->size[2] - i) % d->size[2];
		check_mix(d);
		check_forward(d);
		check_reverse(d);
	}
}
