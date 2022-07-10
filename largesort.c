/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:58:09 by obibby            #+#    #+#             */
/*   Updated: 2022/07/10 21:58:45 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rec_sort(int *stack1, int *stack2, t_info *info)
{
	if (stack1[0] > stack1[1] && stack1[0] != info->max1)
	{
		if (stack2[0] < stack2[1] && stack2[0] != info->min2)
		{
			swap_both(stack1, stack2);
			info->moveno++;
		}
		else
		{
			swap(stack1, "sa\n");
			info->moveno++;
		}
	}
	else if (stack2[0] < stack2[1] && stack2[0] != info->min2)
	{
		swap(stack2, "sb\n");
		info->moveno++;
	}
	else
	{
		stack_rotate(stack1, info->size1, 1, "rr\n");
		stack_rotate(stack2, info->size2, 1, "");
		info->moveno++;
	}
}

int	prepsort(int *stack1, int *stack2, int n, int total)
{
	int		i;
	t_info	info;

	i = 0;
	info.size1 = total;
	info.size2 = 0;
	info.moveno = 0;
	while (i < total)
	{
		if (stack1[0] > n)
		{
			ft_printf("pb\n");
			push_to(stack1, stack2, info.size1, info.size2);
			info.size1--;
			info.size2++;
			info.moveno++;
		}
		else
		{
			ft_printf("%d, %d, %d\n", stack1[0], stack1[1], stack1[2]);
			stack_rotate(stack1, info.size1, 1, "ra\n");
			info.moveno++;
			ft_printf("%d, %d, %d\n", stack1[0], stack1[1], stack1[2]);
		}
		i++;
		if (check_sorted(stack1, 1, info) == 1
			&& check_sorted(stack2, 2, info) == 1)
		{
			info.min1 = find_min(stack1, info.size1);
			recombine_a(stack1, stack2, &info);
			return (info.moveno);
		}
	}
	info.max1 = find_max(stack1, info.size1);
	info.max2 = find_max(stack2, info.size2);
	info.min1 = find_min(stack1, info.size1);
	info.min2 = find_min(stack2, info.size2);
	while (check_sorted(stack1, 1, info) == 0
		|| check_sorted(stack2, 2, info) == 0)
		rec_sort(stack1, stack2, &info);
	recombine_a(stack1, stack2, &info);
	return (info.moveno);
}
