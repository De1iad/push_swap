/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:54:35 by obibby            #+#    #+#             */
/*   Updated: 2022/07/09 22:23:12 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <limits.h>

typedef struct s_info {
	int	moveno;
	int	size1;
	int	size2;
	int	max1;
	int	max2;
	int	min1;
	int	min2;
}	t_info;

int		push_to(int *src, int *dest, t_info *info, int stack);
void	stack_rotate(int *stack, int size, int dir, char *str);
void	swap(int *stack, char *str);

int sort3(int *stack)
{	
	if (stack[2] < stack[0] && stack[1] < stack[0])
	{
		stack_rotate(stack, 3, 1, "ra\n");
		if (stack[0] > stack[1])
			swap(stack, "sa\n");
	}
	else if (stack[2] > stack[0] && stack[1] > stack[0])
	{
		swap(stack, "sa\n");
		stack_rotate(stack, 3, 1, "ra\n");
	}
	else if (stack[2] > stack[0])
		swap(stack, "sa\n");
	else if (stack[1] > stack[0])
		stack_rotate(stack, 3, -1, "rra\n");
	return (0);
}

int smallsort(int *stack, int size)
{
	if (size == 2)
		swap(stack, "sa\n");
	else if (size == 3)
		sort3(stack);
	return (0);
}

int	checkchars(char **argv, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i++ < size)
	{
		while (argv[i][j])
		{
			if ((argv[i][j] == '-' && (argv[i][j + 1] < '0' || argv[i][j] > '9'))
				|| ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '-'))
				return (1);
			j++;
		}
		j = 0;
	}
	return (0);
}

int	checkinput(char **argv, int size)
{
	int	i;
	int	j;
	int	ord;

	i = 0;
	j = 0;
	ord = 2;
	if (checkchars(argv, size) == 1)
		return (1);
	while (i++ < size)
	{
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < INT_MIN)
			return (1);
		if (ord == 2 && i < size && ft_atoi(argv[i + 1]) < ft_atoi(argv[i]))
			ord = 0;
		while (j++ < size)
		{
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]) && i != j)
				return (1);
		}
		j = 0;
	}
	return (ord);
}

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
	x = 0;
	while (i < size)
	{
		if (stack[i] > x)
			x = stack[i];
		i++;
	}
	return (x);
}

void	stack_rotate(int *stack, int size, int dir, char *str)
{
	int	i;
	int	temp;

	i = 0;
	ft_printf("%s", str);
	if (dir == 1)
	{
		temp = stack[0];
		while (++i <= size - 1)
			stack[i - 1] = stack[i];
		stack[size - 1] = temp;
	}
	if (dir == -1)
	{
		i = size - 1;
		temp = stack[i];
		while (i-- > 0)
			stack[i + 1] = stack[i];
		stack[0] = temp;
	}
}

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

int	check_sorted(int *stack, int n, t_info info)
{
	int	i;
	int	sorted;

	i = 1;
	sorted = 1;
	if (n == 1)
	{
		if (stack[0] < stack[info.size1 - 1] && stack[info.size1 - 1] != info.max1)
			sorted = 0;
		while (i <= info.size1 - 1)
		{
			if (stack[i - 1] > stack[i] && (stack[i - 1] != info.max1 || stack[i] != info.min1))
				sorted = 0;
			i++;
		}
	}
	if (n == 2)
	{
		if (stack[0] > stack[info.size2 - 1] && stack[info.size2 - 1] != info.min2)
			sorted = 0;
		while (i <= info.size2 - 1)
		{
			if (stack[i - 1] < stack[i] && (stack[i - 1] != info.min2 || stack[i] != info.max2))
				sorted = 0;
			i++;
		}
	}
	return (sorted);
}

void	recombine_a(int *stack1, int *stack2, t_info *info)
{
	int 	i;
	char	*str;

	i = 0;
	while (stack1[0] != info->min1)
	{
		stack_rotate(stack1, info->size1, 1, "ra\n");
		info->moveno++;
	}
	while (stack2[0] != info->max2)
	{
		stack_rotate(stack2, info->size2, 1, "rb\n");
		info->moveno++;
	}
	while (info->size2 > 0)
	{
		push_to(stack2, stack1, info, 2);
		info->size1++;
		info->size2--;
		info->moveno++;
	}
	while (stack1[i] != info->min1)
		i++;
	if (i > (info->size1 + info->size2) / 2)
	{
		str = "rra\n";
		i = -1;
	}
	else
	{
		str = "ra\n";
		i = 1;
	}
	while (stack1[0] != info->min1)
	{
		stack_rotate(stack1, info->size1, i, str);
		info->moveno++;
	}
}

int	push_to(int *src, int *dest, t_info *info, int stack)
{
	if (stack == 1)
	{
		ft_printf("pb\n");
		stack_shift(dest, info->size2, -1);
		dest[0] = src[0];
		src[0] = 0;
		stack_shift(src, info->size1, 1);
	}
	if (stack == 2)
	{
		ft_printf("pa\n");
		stack_shift(dest, info->size1, -1);
		dest[0] = src[0];
		src[0] = 0;
		stack_shift(src, info->size2, 1);
	}
	return (0);
}

void	swap(int *stack, char *str)
{
	int	temp;

	ft_printf("%s", str);
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

void swap_both(int *stack1, int *stack2)
{
	swap(stack1, "ss\n");
	swap(stack2, "");
}

void rec_sort(int *stack1, int *stack2, t_info *info)
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

int prepsort(int *stack1, int *stack2, int n, int total)
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
			push_to(stack1, stack2, &info, 1);
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
		if (check_sorted(stack1, 1, info) == 1 && check_sorted(stack2, 2, info) == 1)
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
	while (check_sorted(stack1, 1, info) == 0 || check_sorted(stack2, 2, info) == 0)
		rec_sort(stack1, stack2, &info);
	recombine_a(stack1, stack2, &info);
	return (info.moveno);
}

int	main(int argc, char *argv[])
{
	int	*stack1;
	int	*stack2;
	int	i;
	int	sum;

	sum = 0;
	if (argc == 1)
		return (0);
	i = checkinput(argv, argc - 1);
	if (i == 1)
		write(STDERR_FILENO, "Error\n", 6);
	if (i > 0)
		return (0);
	stack1 = ft_calloc(argc + 1, sizeof(int));
	stack2 = ft_calloc(argc + 1, sizeof(int));
	i = 0;
	while (argv[++i])
	{
		stack1[i - 1] = ft_atoi(argv[i]);
		sum += stack1[i - 1];
	}
	if (argc > 4)
		prepsort(stack1, stack2, sum / (argc - 1), argc - 1);
	else 
		smallsort(stack1, argc - 1);
	ft_printf("%d, %d, %d\n", stack1[0], stack1[1], stack1[2]);
	free(stack1);
	free(stack2);
	return (0);
}
