/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:39:48 by obibby            #+#    #+#             */
/*   Updated: 2022/08/09 22:02:38 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sorted(int *stack, t_info *info)
{
	int i;
	int	n;

	i = 0;
	n = 0;
	while (i++ < info->size[1])
		if (stack[i] < stack[n])
			n = i;
	i = 0;
	while (i++ < info->size[1])
		if (stack[(n + i) % info->size[1]] > stack[(n + i + 1) % info->size[1]])
			return (1);
	return (0);
}

void	push_m2(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int i;
	int	j;
	int	keep;

	j = 0;
	while (sorted[j] != stack1[info->best_index])
		j++;
	while (info->size[1] > info->best_count)
	{
		i = -1;
		keep = 0;
		while (++i < info->best_count)
		{
			if (stack1[0] == sorted[(j + i) % info->total])
			{
				stack_rotate(info, 1, 1, "ra\n");
				keep = 1;
				break ;
			}
		}
		if (keep == 0)
		    push_to(stack1, stack2, info, 1);
	}
	/*i = 0;
	while (i < info->size[1])
		ft_printf("%d ", stack1[i++]);
	ft_printf("\n");
	i = 0;
	while (i < info->size[2])
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
	info->min1 = find_min(stack1, info->size[1]);
	while (stack1[i++] != info->min1);
	while (stack1[0] != info->min1)
	{
		if (i < info->total / 2)
			stack_rotate(info, 1, 1, "ra\n");
		else
			stack_rotate(info, 1, -1, "rra\n");
	}
}

void	rotate_both(int dir, t_info *info)
{
	if (dir == 1)
	{
		stack_rotate(info, 1, 1, "rr\n");
		stack_rotate(info, 2, 1, "");
	}
	else if (dir == -1)
	{
		stack_rotate(info, 1, -1, "rrr\n");
		stack_rotate(info, 2, -1, "");
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
	info->min1 = find_min(stack1, info->size[1]);
	info->max1 = find_max(stack1, info->size[1]);
	while (++i < info->size[2])
	{
		j = 0;
		if (stack1[j] < stack2[i] && stack2[i] < info->max1)
			while (stack1[j] < stack2[i])
				j++;
		else if (stack2[i] > info->min1 && stack2[i] < info->max1)
		{
			if (stack1[info->size[1] - 1] > stack2[i])
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
		if (info->size[2] - i >= info->size[1] - j)
			mc_rrr = info->size[2] - i;
		else if (info->size[2] - i < info->size[1] - j)
			mc_rrr = info->size[1] - j;
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
			info->rotate_1 = info->size[1] - j;
			info->rotate_2 = info->size[2] - i;
			info->best_count = mc_rrr;
		}
	}
}

void	sort_b(int *stack1, int *stack2, t_info *info)
{
	//int i;

	while (info->size[2] > 0)
	{
		check_path(stack1, stack2, info);
		if (info->best_method == 1)
		{
			while (info->rotate_1 > 0 && info->rotate_2 > 0)
			{
				rotate_both(1, info);
				info->rotate_1--;
				info->rotate_2--;
			}
			while (info->rotate_1-- > 0)
				stack_rotate(info, 1, 1, "ra\n");
			while (info->rotate_2-- > 0)
				stack_rotate(info, 2, 1, "rb\n");
		}
		if (info->best_method == 2)
		{
			while (info->rotate_1 > 0 && info->rotate_2 > 0)
			{
				rotate_both(-1, info);
				info->rotate_1--;
				info->rotate_2--;
			}
			while (info->rotate_1-- > 0)
				stack_rotate(info, 1, -1, "rra\n");
			while (info->rotate_2-- > 0)
				stack_rotate(info, 2, -1, "rrb\n");
		}
		push_to(stack1, stack2, info, -1);
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
	int	i;
	int	j;
	int	n;

	i = 0;
	info->start_val = stack1[info->best_index];
	info->previous_val = info->start_val;
	while (info->best_index + i < info->total)
	{
		if (stack1[info->best_index + i] > info->previous_val)
			info->previous_val = stack1[info->best_index + i];
		i++;
	}
	i = 0;
	while (i++ < info->total && sorted(stack1, info) == 1)
	{
		j = -1;
		n = 0;
		info->current_val = info->start_val;
		while (stack1[n] != info->current_val)
			n++;
		while (++j < info->size[1])
		{
			if (info->current_val == stack1[0])
			{
				//ft_printf("current: %d, previous: %d\n", info->current_val, info->previous_val);
				if (info->previous_val < stack1[1] && info->current_val > stack1[1] && info->trial > 2)
					swap(stack1, info, "sa\n");
				info->previous_val = info->current_val;
				stack_rotate(info, 1, 1, "ra\n");
				break;
			}
			if (stack1[(n + j + 1) % info->size[1]] > info->current_val)
				info->current_val = stack1[(n + j + 1) % info->size[1]];
			//ft_printf("current: %d\n", info->current_val);
		}
		if (j == info->size[1])
		    push_to(stack1, stack2, info, 1);
	}
	if (stack1[0] > stack1[1] && stack1[info->size[1] - 1] < stack1[1])
		swap(stack1, info, "sa\n");
	/*i = 0;
	while (i < info->size[1])
		ft_printf("%d ", stack1[i++]);
	ft_printf("\n");
	pause();*/
	sort_b(stack1, stack2, info);
	rotate_to_order(stack1, info);
}

void	m2_begin(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (i < info->total)
	{
		count = 1;
		info->current_index = 0;
		j = 0;
		while (stack1[i] != sorted[info->current_index])
			info->current_index++;
		while (j++ < info->total)
		{
			if (stack1[(i + j) % info->total] == sorted[(info->current_index + count) % info->total])
				count++;
		}
		if (count > info->best_count)
		{
			info->best_count = count;
			info->best_index = i;
		}
		i++;
	}
	push_m2(stack1, stack2, sorted, info);
}

void	m1_begin(int *stack1, int *stack2, t_info *info)
{
	int	i;
	int	j;
	int	count;
	int	swap;

	i = 0;
	while (i < info->total)
	{
		count = 1;
		j = -1;
		swap = 0;
		info->current_val = stack1[i];
		while (++j < info->total)
		{
			if (info->current_val < stack1[(i + j) % info->total])
			{
				info->previous_val = info->current_val;
				info->current_val = stack1[(i + j) % info->total];
				count++;
				//ft_printf("count: %d, current val: %d, previous val: %d\n", count, info->current_val, info->previous_val);
				if (stack1[(i + j + 1) % info->total] < info->current_val && stack1[(i + j + 1) % info->total] > info->previous_val && info->trial > 2)
					swap++;
			}
		}
		if (count + swap > info->best_count || (count + swap == info->best_count && swap < info->swap_count))
		{
			info->best_count = count + swap;
			info->best_index = i;
			info->swap_count = swap;
		}
		i++;
	}
	//ft_printf("index: %d, count: %d, swap: %d\n", info->best_index, info->best_count, info->swap_count);
	push_m1(stack1, stack2, info);
}
