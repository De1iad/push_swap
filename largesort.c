/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:39:48 by obibby            #+#    #+#             */
/*   Updated: 2022/08/07 20:42:06 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_m2(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int i;
	int	j;
	int	keep;

	j = 0;
	while (sorted[j] != stack1[info->best_index])
		j++;
	while (info->size1 > info->best_count)
	{
		i = -1;
		keep = 0;
		while (++i < info->best_count)
		{
			if (stack1[0] == sorted[j + i])
			{
				stack_rotate(stack1, info->size1, 1, "ra\n");
				keep = 1;
				break ;
			}
		}
		if (keep == 0)
		{
			ft_printf("pb\n");
		    push_to(stack1, stack2, info->size1--, info->size2++);
		}
	}
	/*i = 0;
	while (i < info->size1)
		ft_printf("%d ", stack1[i++]);
	ft_printf("\n");
	i = 0;
	while (i < info->size2)
		ft_printf("%d ", stack2[i++]);
	ft_printf("\n");
	pause();*/
	sort_b(stack1, stack2, info);
	rotate_to_order(stack1, info);
}

void	rotate_to_order(int *stack1, t_info *info)
{
	int	i;

	i = 0;
	info->min1 = find_min(stack1, info->size1);
	while (stack1[i++] != info->min1);
	while (stack1[0] != info->min1)
	{
		if (i < info->total / 2)
			stack_rotate(stack1, info->size1, 1, "ra\n");
		else
			stack_rotate(stack1, info->size1, -1, "rra\n");
	}
}

void	rotate_both(int *stack1, int *stack2, int dir, t_info *info)
{
	if (dir == 1)
	{
		stack_rotate(stack1, info->size1, 1, "rr\n");
		stack_rotate(stack2, info->size2, 1, "");
	}
	else if (dir == -1)
	{
		stack_rotate(stack1, info->size1, -1, "rrr\n");
		stack_rotate(stack2, info->size2, -1, "");
	}
}

void	check_path(int *stack1, int *stack2, t_info *info)
{
	int	i;
	int	j;
	int	mc_rr;
	int	mc_rrr;

	i = -1;
	info->best_count = info->total;
	info->min1 = find_min(stack1, info->size1);
	info->max1 = find_max(stack1, info->size1);
	while (++i < info->size2)
	{
		j = 0;
		if (stack1[j] < stack2[i] && stack2[i] < info->max1)
			while (stack1[j] < stack2[i])
				j++;
		else if (stack2[i] > info->min1 && stack2[i] < info->max1)
		{
			if (stack1[info->size1 - 1] > stack2[i])
			{
				while (stack1[j] > stack2[i])
					j++;
				while (stack1[j] < stack2[i])
					j++;
			}
		}
		else if (stack2[i] > info->max1)
			while (stack1[j++] != info->max1);
		else if (stack2[i] < info->min1)
		{
			while (stack1[j] != info->min1)
				j++;
		}
		if (i >= j)
			mc_rr = i;
		else if (i < j)
			mc_rr = j;
		if (info->size2 - i >= info->size1 - j)
			mc_rrr = info->size2 - i;
		else if (info->size2 - i < info->size1 - j)
			mc_rrr = info->size1 - j;
		if (mc_rr < mc_rrr && mc_rr < info->best_count)
		{
			info->best_method = 1;
			info->best_val = stack2[i];
			info->rotate_1 = j;
			info->rotate_2 = i;
			info->best_count = mc_rr;
		}
		else if (mc_rrr < mc_rr && mc_rrr < info->best_count)
		{
			info->best_method = 2;
			info->best_val = stack2[i];
			info->rotate_1 = info->size1 - j;
			info->rotate_2 = info->size2 - i;
			info->best_count = mc_rrr;
		}
	}
}

void	sort_b(int *stack1, int *stack2, t_info *info)
{
	//int i;

	while (info->size2 > 0)
	{
		check_path(stack1, stack2, info);
		if (info->best_method == 1)
		{
			while (info->rotate_1 > 0 && info->rotate_2 > 0)
			{
				rotate_both(stack1, stack2, 1, info);
				info->rotate_1--;
				info->rotate_2--;
			}
			while (info->rotate_1-- > 0)
				stack_rotate(stack1, info->size1, 1, "ra\n");
			while (info->rotate_2-- > 0)
				stack_rotate(stack2, info->size2, 1, "rb\n");
		}
		if (info->best_method == 2)
		{
			while (info->rotate_1 > 0 && info->rotate_2 > 0)
			{
				rotate_both(stack1, stack2, -1, info);
				info->rotate_1--;
				info->rotate_2--;
			}
			while (info->rotate_1-- > 0)
				stack_rotate(stack1, info->size1, -1, "rra\n");
			while (info->rotate_2-- > 0)
				stack_rotate(stack2, info->size2, -1, "rrb\n");
		}
		ft_printf("pa\n");
		push_to(stack2, stack1, info->size2--, info->size1++);
		/*i = 0;
		while (i < info->size1)
			ft_printf("%d ", stack1[i++]);
		ft_printf("\n");
		i = 0;
		while (i < info->size2)
			ft_printf("%d ", stack2[i++]);
		ft_printf("\n");
		sleep(1);*/
	}
}

void	push_m1(int *stack1, int *stack2, t_info *info)
{
	//int	i;
	int	j;
	int	n;

	//i = 0;
	info->start_val = stack1[info->best_index];
	while (/*i++ < info->total && */info->size1 > info->best_count)
	{
		j = -1;
		n = 0;
		info->current_val = info->start_val;
		while (stack1[n] != info->current_val)
			n++;
		while (++j < info->size1)
		{
			if (info->current_val == stack1[0])
			{
				if (info->previous_val < stack1[1] && info->current_val > stack1[1])
				{
					info->best_count++;
					swap(stack1, "sa\n");
				}
				info->previous_val = info->current_val;
				stack_rotate(stack1, info->size1, 1, "ra\n");
				break;
			}
			if (stack1[(n + j) % info->size1] >= info->current_val)
				info->current_val = stack1[(n + j) % info->size1];
		}
		if (j == info->size1)
		{
			ft_printf("pb\n");
		    push_to(stack1, stack2, info->size1--, info->size2++);
		}
	}
	sort_b(stack1, stack2, info);
	rotate_to_order(stack1, info);
}

void	largesort(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (i < info->total)
	{
		count = 0;
		j = -1;
		info->current_val = stack1[i];
		while (++j < info->total)
		{
			if (info->current_val < stack1[(i + j) % info->total])
			{
				info->current_val = stack1[(i + j) % info->total];
				count++;
			}
		}
		if (count > info->best_count)
		{
			info->best_count = count;
			info->best_index = i;
			info->best_method = 1;
		}
		i++;
	}
	i = 0;
	while (i < info->total)
	{
		count = 0;
		info->current_index = 0;
		j = -1;
		while (stack1[i] != sorted[info->current_index])
			info->current_index++;
		while (++j < info->total)
		{
			if (stack1[(i + j) % info->total] == sorted[(info->current_index + count) % info->total])
				count++;
		}
		if (count > info->best_count)
		{
			info->best_count = count;
			info->best_index = i;
			info->best_method = 2;
		}
		i++;
	}
	if (info->best_method == 1)
		push_m1(stack1, stack2, info);
	else if (info->best_method == 2)
		push_m2(stack1, stack2, sorted, info);
}
