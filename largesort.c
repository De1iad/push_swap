/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:58:09 by obibby            #+#    #+#             */
/*   Updated: 2022/07/11 23:22:20 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_mean(int *stack, int size)
{
	int i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < size)
		sum += stack[i++];
	return (sum / size);
}

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

int	meansorta(int *stack1, int *stack2, int count, t_info *info)
{
	int	n;
	int	mean;
	int	x;

	x = count;
	while (count > 2)
	{
		n = 0;
		mean = find_mean(stack1, count);
		while (count > 2 && n < count)
		{
			if (stack1[0] < mean)
			{
				ft_printf("pb\n");
				push_to(stack1, stack2, info->size1--, info->size2++);
				count--;
				if (stack2[0] < stack2[1] && info->size2 > 1)
				{
					if (stack1[0] > stack1[1] && count > 2)
						swap_both(stack1, stack2);
					else
						swap(stack2, "sb\n");
				}
			}
			else
			{
				stack_rotate(stack1, info->size1, 1, "ra\n");
				n++;
			}
		}
		while (n-- > 0)
			stack_rotate(stack1, info->size1, -1, "rra\n");
	}
	if (count == 2)
	{
		if (stack1[0] > stack1[1])
		{
			if (stack2[0] < stack2[1])
				swap_both(stack1, stack2);
			else
				swap(stack1, "sa\n");
		}
		ft_printf("pb\n");
		push_to(stack1, stack2, info->size1--, info->size2++);
		ft_printf("pb\n");
		push_to(stack1, stack2, info->size1--, info->size2++);
	}
	meansortb(stack1, stack2, x, info);
	return (0);
}

int	meansortb(int *stack1, int *stack2, int count, t_info *info)
{
	int	n;
	int	mean;
	int	x;
	//int i;

	x = count;
	if (count == 1)
	{
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2--, info->size1++);
		return (0);
	}
	while (count > 2)
	{
		n = 0;
		mean = find_mean(stack2, count);
		while (count > 2 && n < count)
		{
			if (stack2[0] > mean)
			{
				ft_printf("pa\n");
				push_to(stack2, stack1, info->size2--, info->size1++);
				count--;
				if (stack1[0] > stack1[1] && info->size1 > 1)
				{
					if (stack2[0] < stack2[1] && count > 2)
						swap_both(stack1, stack2);
					else
						swap(stack1, "sa\n");
				}
			}
			else
			{
				stack_rotate(stack2, info->size2, 1, "rb\n");
				n++;
			}
		}
		while (n-- > 0)
			stack_rotate(stack2, info->size2, -1, "rrb\n");
	}
	if (count == 2)
	{
		if (stack2[0] < stack2[1])
		{
			if (stack1[0] > stack1[1])
				swap_both(stack1, stack2);
			else
				swap(stack2, "sb\n");
		}
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2--, info->size1++);
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2--, info->size1++);
	}
	/*if (stack2[0] == 40 || stack2[1] == 40 || stack2[2] == 40)
	{
		i = 0;
		while (i < x)
			ft_printf("%d, ", stack1[i++]);
		ft_printf("\n");
		i = 0;
		while (i < info->size1)
			ft_printf("%d, ", stack2[i++]);
		ft_printf("\n");
		ft_printf("size1: %d, size2: %d\n", info->size1, info->size2);
		ft_printf("count: %d\n", count);
		pause();
	}*/
	if (check_sorted(stack1, x, 1) != 1)
		meansorta(stack1, stack2, x, info);
	return (0);
}

int	meansort(int *stack1, int *stack2, int mean, t_info *info)
{
	int	i;
	int	count;
	int	size;
	//int j;

	i = 0;
	count = 0;
	size = info->size1;
	while (i < size)
	{
		if (stack1[0] < mean)
		{
			ft_printf("pb\n");
			push_to(stack1, stack2, info->size1--, info->size2++);
			count++;
		}
		else
			stack_rotate(stack1, info->size1, 1, "ra\n");
		i++;
	}
	/*j = 0;
	while (j < count)
	{
		if (stack2[j++] == 40)
		{
			i = 0;
			while (i < info->size1)
				ft_printf("%d, ", stack1[i++]);
			ft_printf("\n");
			i = 0;
			while (i < info->size2)
				ft_printf("%d, ", stack2[i++]);
			ft_printf("\n");
			ft_printf("count: %d\n", count);
			ft_printf("size1: %d, size2: %d\n", info->size1, info->size2);
			sleep(5);
		}
	}*/
	if (info->sort == 0 && info->size1 > 2)
		meansort(stack1, stack2, find_mean(stack1, info->size1), info);
	info->sort = 1;
	if (info->size1 == 2 && stack1[0] > stack1[1])
		swap(stack1, "sa\n");
	meansortb(stack1, stack2, count, info);
	if (info->size2 == 1)
	{
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2--, info->size1++);
	}
	return (0);
}
