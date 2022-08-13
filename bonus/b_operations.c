/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:02:07 by obibby            #+#    #+#             */
/*   Updated: 2022/08/12 22:37:53 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	stack_shift(int *stack, int size, int dir)
{
	int	i;

	i = 0;
	if (dir == 1)
	{
		while (i < size - 1)
		{
			stack[i] = stack[i + 1];
			i++;
		}
		stack[i] = '\0';
	}
	else
	{
		while (i <= size - 1)
			i++;
		while (i > 0)
		{
			stack[i] = stack[i - 1];
			i--;
		}
		stack[0] = '\0';
	}
}

void	stack_rotate(t_info *d, int s_id, int dir)
{
	int	i;
	int	temp;

	if ((s_id == 1 && d->size[1] < 2) || (s_id == 0 && d->size[0] < 2))
		return ;
	i = 0;
	if (dir == 1)
	{
		temp = d->stack[s_id][0];
		while (++i <= d->size[s_id] - 1)
			d->stack[s_id][i - 1] = d->stack[s_id][i];
		d->stack[s_id][d->size[s_id] - 1] = temp;
	}
	else if (dir == -1)
	{
		i = d->size[s_id] - 1;
		temp = d->stack[s_id][i];
		while (i-- > 0)
			d->stack[s_id][i + 1] = d->stack[s_id][i];
		d->stack[s_id][0] = temp;
	}
}

void	push_to(int *stack1, int *stack2, t_info *d, int dir)
{
	if (dir == 1)
	{
		if (d->size[0] == 0)
			return ;
		stack_shift(stack2, d->size[1]++, -1);
		stack2[0] = stack1[0];
		stack1[0] = 0;
		stack_shift(stack1, d->size[0]--, 1);
	}
	if (dir == -1)
	{
		if (d->size[1] == 0)
			return ;
		stack_shift(stack1, d->size[0]++, -1);
		stack1[0] = stack2[0];
		stack2[0] = 0;
		stack_shift(stack2, d->size[1]--, 1);
	}
}

void	swap(int *stack, t_info *d, int id)
{
	int	temp;

	if ((id == 0 && d->size[0] < 2) || (id == 1 && d->size[1] < 2))
		return ;
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

void	swap_both(int *stack1, int *stack2, t_info *d)
{
	swap(stack1, d, 0);
	swap(stack2, d, 1);
}
