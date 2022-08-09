/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:02:07 by obibby            #+#    #+#             */
/*   Updated: 2022/08/09 22:15:36 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	stack_rotate(t_info *info, int s_id, int dir, char *str)
{
	int	i;
	int	temp;

	i = 0;
	if (info->trial == 0 || info->trial > 3)
		ft_printf("%s", str);
	if (str[0])
		info->m_count[info->trial]++;
	if (dir == 1)
	{
		temp = info->stack[s_id][0];
		while (++i <= info->size[s_id] - 1)
			info->stack[s_id][i - 1] = info->stack[s_id][i];
		info->stack[s_id][info->size[s_id] - 1] = temp;
	}
	if (dir == -1)
	{
		i = info->size[s_id] - 1;
		temp = info->stack[s_id][i];
		while (i-- > 0)
			info->stack[s_id][i + 1] = info->stack[s_id][i];
		info->stack[s_id][0] = temp;
	}
}

int	push_to(int *stack1, int *stack2, t_info *info, int dir)
{
	info->m_count[info->trial]++;
	if (dir == 1)
	{
		if (info->trial == 0 || info->trial > 3)
			ft_printf("pb\n");
		stack_shift(stack2, info->size[2]++, -1);
		stack2[0] = stack1[0];
		stack1[0] = 0;
		stack_shift(stack1, info->size[1]--, 1);
	}
	if (dir == -1)
	{
		if (info->trial == 0 || info->trial > 3)
			ft_printf("pa\n");
		stack_shift(stack1, info->size[1]++, -1);
		stack1[0] = stack2[0];
		stack2[0] = 0;
		stack_shift(stack2, info->size[2]--, 1);
	}
	return (0);
}

void	swap(int *stack, t_info *info, char *str)
{
	int	temp;

	if (info->trial == 0 || info->trial > 3)
		ft_printf("%s", str);
	if (str[0])
		info->m_count[info->trial]++;
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

void	swap_both(int *stack1, int *stack2, t_info *info)
{
	swap(stack1, info, "ss\n");
	swap(stack2, info, "");
}
