/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:32:32 by obibby            #+#    #+#             */
/*   Updated: 2022/08/11 16:48:40 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	legit_function(t_info *d, int *stack1)
{
	if (d->previous_val < stack1[1] && d->current_val > stack1[1]
		&& (d->trial > 2))
		swap(stack1, d, "sa\n");
	d->previous_val = d->current_val;
	stack_rotate(d, 1, 1, "ra\n");
}

void	m1_push(t_info *d, int *stack1, int *stack2, int i)
{
	int	j;
	int	n;

	while (i++ < d->total && sorted(stack1, d) == 1)
	{
		j = -1;
		n = 0;
		d->current_val = d->start_val;
		while (stack1[n] != d->current_val)
			n++;
		while (++j < d->size[1])
		{
			if (d->current_val == stack1[0])
			{
				legit_function(d, stack1);
				break ;
			}
			if (stack1[(n + j + 1) % d->size[1]] > d->current_val)
				d->current_val = stack1[(n + j + 1) % d->size[1]];
		}
		if (j == d->size[1])
			push_to(stack1, stack2, d, 1);
	}
}

void	m1_act(int *stack1, int *stack2, t_info *d)
{
	int	i;

	i = 0;
	d->start_val = stack1[d->best_index];
	d->previous_val = d->start_val;
	while (d->best_index + i < d->total)
	{
		if (stack1[d->best_index + i] > d->previous_val)
			d->previous_val = stack1[d->best_index + i];
		i++;
	}
	m1_push(d, stack1, stack2, 0);
	if (stack1[0] > stack1[1] && stack1[d->size[1] - 1] < stack1[1])
		swap(stack1, d, "sa\n");
	sort_b(stack1, stack2, d);
	rotate_to_order(stack1, d);
}

void	get_count_m1(t_info *d, int *i, int *j)
{
	if (d->current_val < d->stack[1][(*i + *j) % d->total])
	{
		d->previous_val = d->current_val;
		d->current_val = d->stack[1][(*i + *j) % d->total];
		d->count++;
		if (d->stack[1][(*i + *j + 1) % d->total] < d->current_val
			&& d->stack[1][(*i + *j + 1) % d->total] > d->previous_val
			&& (d->trial > 2))
			d->swap++;
	}
}

void	m1_plan(int *stack1, int *stack2, t_info *d)
{
	int	i;
	int	j;

	i = -1;
	while (++i < d->total)
	{
		d->count = 1;
		j = -1;
		d->swap = 0;
		d->current_val = stack1[i];
		while (++j < d->total)
			get_count_m1(d, &i, &j);
		if (d->count + d->swap > d->best_count
			|| (d->count + d->swap == d->best_count
				&& d->swap < d->swap_count))
		{
			d->best_count = d->count + d->swap;
			d->best_index = i;
			d->swap_count = d->swap;
		}
	}
	m1_act(stack1, stack2, d);
}
