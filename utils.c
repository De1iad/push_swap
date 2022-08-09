/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:51:19 by obibby            #+#    #+#             */
/*   Updated: 2022/08/07 22:11:12 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_rem(int *stack1, int *stack2, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->size[1] - 1)
	{
		if (stack1[i] > stack2[0] && ((i > 0 && (stack1[i - 1] < stack2[0]
						|| stack1[i - 1] == info->max1))
				|| stack1[3] == info->max1 || stack1[3] < stack2[0]))
			break ;
		i++;
	}
	if (i == 1 || i == 2)
		while (i-- > 0)
			stack_rotate(info, 1, 1, "ra\n");
	else if (i > 2)
		stack_rotate(info, 1, -1, "rra\n");
	push_to(stack1, stack2, info, -1);
}
