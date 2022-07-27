/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:49:26 by obibby            #+#    #+#             */
/*   Updated: 2022/07/24 13:00:58 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort3swap(int *stack1, int *stack2)
{
	swap(stack2, "");
	if (stack1[2] < stack1[0] && stack1[1] < stack1[0])
	{
		stack_rotate(stack1, 3, 1, "rr\n");
		if (stack1[0] > stack1[1])
			swap(stack1, "sa\n");
	}
	else if (stack1[2] > stack1[0] && stack1[1] > stack1[0])
	{
		swap(stack1, "ss\n");
		stack_rotate(stack1, 3, 1, "ra\n");
	}
	else if (stack1[2] > stack1[0])
		swap(stack1, "ss\n");
	else if (stack1[1] > stack1[0])
		stack_rotate(stack1, 3, -1, "rrr\n");
	return (0);
}

int	sort3(int *stack1)
{	
	if (stack1[2] < stack1[0] && stack1[1] < stack1[0])
	{
		stack_rotate(stack1, 3, 1, "ra\n");
		if (stack1[0] > stack1[1])
			swap(stack1, "sa\n");
	}
	else if (stack1[2] > stack1[0] && stack1[1] > stack1[0])
	{
		swap(stack1, "sa\n");
		stack_rotate(stack1, 3, 1, "ra\n");
	}
	else if (stack1[2] > stack1[0])
		swap(stack1, "sa\n");
	else if (stack1[1] > stack1[0])
		stack_rotate(stack1, 3, -1, "rra\n");
	return (0);
}

void	sortstacks5(int *stack1, int *stack2, t_info *info)
{
	ft_printf("pb\n");
	push_to(stack1, stack2, info->size1--, info->size2++);
	ft_printf("pb\n");
	push_to(stack1, stack2, info->size1--, info->size2++);
	info->min1 = find_min(stack1, info->size1);
	if (stack1[0] < stack1[1] && stack1[1] < stack1[2]
		&& stack2[0] < stack2[1] && stack1[0] < stack2[1])
	{
		if (stack2[1] == info->max1)
			ft_printf("sb\n");
		else if (stack2[1] > stack1[1])
			stack_rotate(stack1, 3, -1, "rrr\n");
		else
			stack_rotate(stack1, 3, 1, "rr\n");
		swap(stack2, "");
	}
	else if (stack2[0] < stack2[1] && (stack1[0] > stack1[1]
			|| stack1[1] > stack1[2]))
		sort3swap(stack1, stack2);
	else if (stack1[0] > stack1[1] || stack1[1] > stack1[2])
		sort3(stack1);
}

void	sort5(int *stack1, int *stack2, t_info *info)
{
	int	i;

	i = 0;
	sortstacks5(stack1, stack2, info);
	while (stack1[i] < stack2[0])
		i++;
	if (i == 1)
		stack_rotate(stack1, info->size1, 1, "ra\n");
	else if (i > 1)
		while (stack1[info->size1 - 1] > stack2[0] && i-- > 0)
			stack_rotate(stack1, info->size1, -1, "rra\n");
	ft_printf("pa\n");
	push_to(stack2, stack1, info->size2--, info->size1++);
	sort_rem(stack1, stack2, info);
	info->min1 = find_min(stack1, info->size1);
	i = 0;
	while (stack1[i] != info->min1)
		i++;
	if (i > 2)
		while (stack1[0] != info->min1)
			stack_rotate(stack1, info->size1, -1, "rra\n");
	else
		while (stack1[0] != info->min1)
			stack_rotate(stack1, info->size1, 1, "ra\n");
}

int	smallsort(int *stack1, int *stack2, t_info *info)
{
	info->max1 = find_max(stack1, info->size1);
	info->min1 = find_min(stack1, info->size1);
	if (info->size1 == 2)
		swap(stack1, "sa\n");
	else if (info->size1 == 3)
		sort3(stack1);
	else if (info->size1 == 4)
	{
		push_to(stack1, stack2, info->size1, 0);
		sort3(stack1);
		push_to(stack2, stack1, 1, info->size1);
	}
	else if (info->size1 == 5)
		sort5(stack1, stack2, info);
	return (0);
}
