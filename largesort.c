/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:39:48 by obibby            #+#    #+#             */
/*   Updated: 2022/08/10 23:57:46 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	find_next(int *stack1, int *stack2, t_info *info)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	info->best_count2 = info->total;
	while ((info->best_method == 1 || info->best_method == 3) && ++i <= info->rotate_2);
	while (info->best_method % 2 == 0 && ++i <= ((info->size[2] - info->rotate_2) % info->size[2]));
	while ((info->best_method == 1 || info->best_method == 3) && ++j < info->rotate_1);
	while (info->best_method % 2 == 0 && ++j < (info->size[1] - info->rotate_1) % info->size[1]);
	info->i0 = i;
	info->j0 = j;
	//ft_printf("i: %d, ival: %d, j: %d, jval: %d, rot2: %d, s0: %d\n", i % info->size[2], stack2[i % info->size[2]], j % info->size[1], stack1[j % info->size[1]], info->rotate_2, stack2[0]);
	while (i - info->i0 < info->size[2] - 1)
	{
		j = info->j0;
		if (stack1[j % info->size[1]] < stack2[i % info->size[2]] && stack2[i % info->size[2]] < info->max1)
			while (stack1[j % info->size[1]] < stack2[i % info->size[2]])
				j++;
		else if (stack2[i % info->size[2]] > info->min1 && stack2[i % info->size[2]] < info->max1)
		{
			if (stack1[info->size[1] - 1] > stack2[i % info->size[2]])
			{
				while (stack1[j % info->size[1]] > stack2[i % info->size[2]])
					j++;
				while (stack1[j % info->size[1]] < stack2[i % info->size[2]])
					j++;
			}
		}
		else if (stack2[i % info->size[2]] > info->max1)
			while (stack1[j++ % info->size[1]] != info->max1);
		else if (stack2[i % info->size[2]] < info->min1)
		{
			while (stack1[j % info->size[1]] != info->min1)
				j++;
		}
		info->rb2 = i - info->i0;
		info->ra2 = j - info->j0;
		info->rrb2 = (info->size[2] - (i - info->i0)) % info->size[2];
		info->rra2 = (info->size[1] - (j - info->j0)) % info->size[1];
		if (info->rb2 + info->rra2 < info->best_count2)
		{
			info->best_count2 = info->rb2 + info->rra2;
			info->dir_next = 1;
			info->val_next = stack2[i % info->size[2]];
		}
		if (info->ra2 + info->rrb2 < info->best_count2)
		{
			info->best_count2 = info->ra2 + info->rrb2;
			info->dir_next = -1;
			info->val_next = stack2[i % info->size[2]];
		}
		if ((info->ra2 < info->rra2 && info->rb2 < info->rra2) || (info->ra2 < info->rrb2 && info->rb2 < info->rrb2))
		{
			if (info->ra2 < info->rb2 && info->rb2 <= info->best_count2)
			{
				info->best_count2 = info->rb2;
				info->dir_next = 1;
				info->val_next = stack2[i % info->size[2]];
			}
			else if (info->rb2 < info->ra2 && info->ra2 <= info->best_count2)
			{
				info->best_count2 = info->ra2;
				info->dir_next = 1;
				info->val_next = stack2[i % info->size[2]];
			}
		}
		else
		{
			if (info->rra2 < info->rrb2 && info->rrb2 <= info->best_count2)
			{
				info->best_count2 = info->rrb2;
				info->dir_next = -1;
				info->val_next = stack2[i % info->size[2]];
			}
			if (info->rrb2 < info->rra2 && info->rra2 <= info->best_count2)
			{
				info->best_count2 = info->rra2;
				info->dir_next = -1;
				info->val_next = stack2[i % info->size[2]];
			}
		}
		i++;
	}
}

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

	i = -1;
	info->best_count = info->total * 2;
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
		info->rb = i;
		info->ra = j;
		info->rrb = (info->size[2] - i) % info->size[2];
		info->rra = (info->size[1] - j) % info->size[1];
		if (info->rb + info->rra < info->best_count)
		{
			info->best_method = 3;
			info->rotate_1 = (info->size[1] - j) % info->size[1];
			info->rotate_2 = i;
			info->best_count = info->rb + info->rra;
		}
		if (info->ra + info->rrb < info->best_count)
		{
			info->best_method = 4;
			info->rotate_1 = j;
			info->rotate_2 = (info->size[2] - i) % info->size[2];
			info->best_count = info->ra + info->rrb;
		}
		if ((info->ra < info->rra && info->rb < info->rra) || (info->ra < info->rrb && info->rb < info->rrb))
		{
			if (info->ra < info->rb && info->rb <= info->best_count)
			{
				info->best_method = 1;
				info->rotate_1 = j;
				info->rotate_2 = i;
				info->best_count = info->rb;
			}
			else if (info->rb < info->ra && info->ra <= info->best_count)
			{
				info->best_method = 1;
				info->rotate_1 = j;
				info->rotate_2 = i;
				info->best_count = info->ra;
			}
		}
		else
		{
			if (info->rra < info->rrb && info->rrb <= info->best_count)
			{
				info->best_method = 2;
				info->rotate_1 = (info->size[1] - j) % info->size[1];
				info->rotate_2 = (info->size[2] - i) % info->size[2];
				info->best_count = info->rrb;
			}
			if (info->rrb < info->rra && info->rra <= info->best_count)
			{
				info->best_method = 2;
				info->rotate_1 = (info->size[1] - j) % info->size[1];
				info->rotate_2 = (info->size[2] - i) % info->size[2];
				info->best_count = info->rra;
			}
		}
	}
	find_next(stack1, stack2, info);
}

void	sort_b(int *stack1, int *stack2, t_info *info)
{
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
			{
				if (info->use_swap == 1 && info->rotate_2 == 0 && info->dir_next == -1)
					swap(stack2, info, "sb\n");
				else
					stack_rotate(info, 2, 1, "rb\n");
			}
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
		if (info->best_method == 3)
		{
			while (info->rotate_1-- > 0)
				stack_rotate(info, 1, -1, "rra\n");
			while (info->rotate_2-- > 0)
			{
				if (info->use_swap == 1 && info->rotate_2 == 0 && info->dir_next == -1)
					swap(stack2, info, "sb\n");
				else
					stack_rotate(info, 2, 1, "rb\n");
			}
		}
		if (info->best_method == 4)
		{
			while (info->rotate_1-- > 0)
				stack_rotate(info, 1, 1, "ra\n");
			while (info->rotate_2-- > 0)
				stack_rotate(info, 2, -1, "rrb\n");
		}
		push_to(stack1, stack2, info, -1);
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
				if (info->previous_val < stack1[1] && info->current_val > stack1[1] && (info->trial == 3 || info->trial > 5))
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
				if (stack1[(i + j + 1) % info->total] < info->current_val && stack1[(i + j + 1) % info->total] > info->previous_val && (info->trial == 3 || info->trial > 5))
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
