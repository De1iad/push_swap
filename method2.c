/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:33:48 by obibby            #+#    #+#             */
/*   Updated: 2022/08/13 10:12:15 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	m2_push(t_info *d, int *sorted, int *j)
{
	int	i;
	int	keep;

	i = -1;
	keep = 0;
	while (++i < d->best_count)
	{
		if (d->stack[1][1] == sorted[(*j + i) % d->total]
			&& d->stack[1][0] == sorted[(*j + i + 1) % d->total])
			swap(d->stack[1], d, "sa\n");
		if (d->stack[1][0] == sorted[(*j + i) % d->total])
		{
			stack_rotate(d, 1, 1, "ra\n");
			keep = 1;
			break ;
		}
	}
	if (keep == 0)
		push_to(d->stack[1], d->stack[2], d, 1);
}

void	m2_act(int *stack1, int *stack2, int *sorted, t_info *d)
{
	int	j;

	j = 0;
	while (sorted[j] != stack1[d->best_index])
		j++;
	while (d->size[1] > d->best_count)
		m2_push(d, sorted, &j);
	sort_b(stack1, stack2, d);
	rotate_to_order(stack1, d);
}

void	get_count_m2(t_info *d, int *sorted, int *i, int *j)
{
	if (d->stack[1][(*i + *j) % d->total]
		== sorted[(d->current_index + d->count) % d->total])
		d->count++;
	else if (*j + 1 < d->total && d->stack[1][(*i + *j + 1) % d->total]
		== sorted[(d->current_index + d->count) % d->total]
		&& d->stack[1][(*i + *j) % d->total]
		== sorted[(d->current_index + d->count + 1) % d->total])
	{
		(*j)++;
		d->count++;
	}	
}

void	m2_plan(int *stack1, int *stack2, int *sorted, t_info *d)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->total)
	{
		d->count = 1;
		d->current_index = 0;
		j = 0;
		while (stack1[i] != sorted[d->current_index])
			d->current_index++;
		while (j++ < d->total)
			get_count_m2(d, sorted, &i, &j);
		if (d->count > d->best_count)
		{
			d->best_count = d->count;
			d->best_index = i;
		}
		i++;
	}
	m2_act(stack1, stack2, sorted, d);
}
