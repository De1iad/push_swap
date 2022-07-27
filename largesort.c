/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:58:09 by obibby            #+#    #+#             */
/*   Updated: 2022/07/24 11:31:55 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_mean(int *stack, int size)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < size)
		sum += stack[i++];
	return (sum / size);
}

void	sortb(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	if (info->divtotal == 7)
		x = 4;
	while (i < info->div + x)
	{
		j = 0;
		while (stack2[j] != sorted[info->div * info->divtotal - i - 1 + x])
			j++;
		if (j == 1)
			swap(stack2, "sb\n");
		else if (j > info->div + x
			&& stack2[0] != sorted[info->div * info->divtotal - i - 1 + x])
		{
			while (stack2[0] != sorted[info->div * info->divtotal - i - 1 + x])
				stack_rotate(stack2, info->size2, -1, "rrb\n");
		}
		else if (stack2[0] != sorted[info->div * info->divtotal - i - 1 + x])
		{
			while (stack2[1] != sorted[info->div * info->divtotal - i - 1 + x])
				stack_rotate(stack2, info->size2, 1, "rb\n");
			while (stack2[j] != sorted[info->div * info->divtotal - i - 2 + x])
				j++;
			if (j > info->div + x)
				swap(stack2, "sb\n");
			else
				stack_rotate(stack2, info->size2, 1, "rb\n");
		}
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2--, info->size1++);
		i++;
	}
}

void	sorta(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int	i;
	int	j;

	i = info->div * (info->divtotal - 1);
	while (i < info->total && info->size1 > 3
		&& check_sorted(stack1, info->size1, 1) != 1)
	{
		j = 0;
		while (stack1[j] != sorted[i])
			j++;
		if (j > (info->div / 2) && stack1[0] != sorted[i])
		{
			while (stack1[0] != sorted[i])
				stack_rotate(stack1, info->size1, -1, "rra\n");
		}
		else if (j <= (info->div / 2) && stack1[0] != sorted[i])
		{
			while (stack1[0] != sorted[i] && stack1[1] != sorted[i])
				stack_rotate(stack1, info->size1, 1, "ra\n");
			if (info->size1 > 3 && stack1[0] < stack1[2])
				swap(stack1, "sa\n");
			else
				stack_rotate(stack1, info->size1, 1, "ra\n");
		}
		ft_printf("pb\n");
		push_to(stack1, stack2, info->size1--, info->size2++);
		i++;
	}
	if (check_sorted(stack1, info->size1, 1) != 1)
		sort3(stack1);
	while (info->size1 < info->div)
	{
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2--, info->size1++);
	}
}

int	meansort(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	while (++x < info->divtotal)
	{
		i = 0;
		while (i++ < info->div)
		{
			j = 0;
			while (j++ < info->size1 - 1)
			{
				if (stack1[info->size1 - 1] < sorted[info->div * x])
				{
					if (stack2[0] < stack2[info->size2 - 1])
					{
						stack_rotate(stack1, info->size1, -1, "rrr\n");
						stack_rotate(stack2, info->size2, -1, "");
					}
					else
						stack_rotate(stack1, info->size1, -1, "rra\n");
					break ;
				}
				else if (stack1[j] < sorted[info->div * x])
				{
					while (j-- > 1)
					{
						if (stack2[0] < stack2[info->size2 - 1])
						{
							stack_rotate(stack1, info->size1, 1, "rr\n");
							stack_rotate(stack2, info->size2, 1, "");
						}
						else
							stack_rotate(stack1, info->size1, 1, "ra\n");
					}
					if (stack1[0] > stack1[1])
					{
						if (info->size2 > 1 && stack2[0] < stack2[1])
							swap_both(stack1, stack2);
						else
							swap(stack1, "sa\n");
					}
					else
						stack_rotate(stack1, info->size1, 1, "ra\n");
					break ;
				}
			}
			ft_printf("pb\n");
			push_to(stack1, stack2, info->size1--, info->size2++);
		}
	}
	sorta(stack1, stack2, sorted, info);
	while (info->divtotal-- > 1)
		sortb(stack1, stack2, sorted, info);
	return (0);
}
