/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:54:35 by obibby            #+#    #+#             */
/*   Updated: 2022/08/09 22:26:19 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//inside check path write function allowing to see multiple moves ahead!

int	find_min(int *stack, int size)
{
	int	i;
	int	x;

	i = 0;
	x = INT_MAX;
	while (i < size)
	{
		if (stack[i] < x)
			x = stack[i];
		i++;
	}
	return (x);
}

int	find_max(int *stack, int size)
{
	int	i;
	int	x;

	i = 0;
	x = INT_MIN;
	while (i < size)
	{
		if (stack[i] > x)
			x = stack[i];
		i++;
	}
	return (x);
}

void	presort(int *stack, char **argv, int *sorted, int size)
{
	int	n;
	int	i;
	int	x;

	i = 0;
	while (argv[++i])
		stack[i - 1] = ft_atoi(argv[i]);
	n = 0;
	while (n < size)
	{
		x = 0;
		i = 0;
		while (i < size)
		{
			if (stack[n] > stack[i++])
				x++;
		}
		sorted[x] = stack[n++];
	}
}

int	main(int argc, char *argv[])
{
	int		*stack1;
	int		*stack2;
	int		*sorted;
	t_info	info;
	//int	i;

	if (checkinput(argv, argc - 1) > 0)
		return (0);
	stack1 = ft_calloc(argc, sizeof(int));
	stack2 = ft_calloc(argc, sizeof(int));
	sorted = ft_calloc(argc, sizeof(int));
	presort(stack1, argv, sorted, argc - 1);
	init_struct(&info, argc, stack1, stack2);
	info.trial = 3;
	info.m_count[0] = 0;
	info.m_count[1] = 0;
	info.m_count[2] = 0;
	info.m_count[3] = 0;
	info.m_count[4] = 0;

	if (argc <= 6)
		smallsort(stack1, stack2, &info);
	else
	{
		m1_begin(stack1, stack2, &info);
		/*i = 0;
		while (i < info.size[1])
			ft_printf("%d ", stack1[i++]);
		ft_printf("\n");*/
		info.trial--;
		presort(stack1, argv, sorted, argc - 1);
		init_struct(&info, argc, stack1, stack2);
		m1_begin(stack1, stack2, &info);
		info.trial--;
		presort(stack1, argv, sorted, argc - 1);
		init_struct(&info, argc, stack1, stack2);
		m2_begin(stack1, stack2, sorted, &info);
		/*i = 0;
		while (i < info.size[1])
			ft_printf("%d ", stack1[i++]);
		ft_printf("\n");
		pause();*/
		info.trial--;
		presort(stack1, argv, sorted, argc - 1);
		/*ft_printf("m1 moves: %d, m2 moves: %d\n", info.m_count[1], info.m_count[2]);
		pause();*/
		init_struct(&info, argc, stack1, stack2);
		/*ft_printf("m1: %d, m2: %d\n", info.m_count[2], info.m_count[1]);
		pause();*/
		if (info.m_count[2] <= info.m_count[1] || info.m_count[3] <= info.m_count[1])
		{
			if (info.m_count[3] <= info.m_count[2])
				info.trial = 4;
			m1_begin(stack1, stack2, &info);
		}
		else
			m2_begin(stack1, stack2, sorted, &info);
	}
	/*i = 0;
	while (i < info.size[1])
		ft_printf("%d ", stack1[i++]);
	ft_printf("\n");*/
	//ft_printf("m1: %d, m2: %d, m3: %d, m4: %d, m0: %d\n", info.m_count[1], info.m_count[2], info.m_count[3], info.m_count[4], info.m_count[0]);
	free(stack1);
	free(stack2);
	free(sorted);
	return (0);
}
