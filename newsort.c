#include "push_swap.h"

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
	while (++i < info->size2)
	{
		j = 0;
		if (stack1[j] < stack2[i] && stack2[i] < info->s1_max)
			while (stack1[j] < stack2[i])
				j++;
		else if (stack2[i] > info->s1_min && stack2[i] < info->s1_max)
			while (stack1[j++] > stack2[i]);
		else if (stack2[i] > info->s1_max)
			while (stack1[j++] != info->s1_max);
		else if (stack2[i] < info->s1_min)
			while (stack1[j] != info->s1_min)
				j++;
		if (i >= j)
			mc_rr = i;
		else if (i < j)
			mc_rr = j;
		if (info->size2 - i >= info->size1 - j)
			mc_rrr = info->size2 - i;
		else if (info->size2 - i < info->size1 - j)
			mc_rrr = info->size1 - j;
		//ft_printf("mc_rr: %d, mc_rrr: %d, i: %d, j: %d, size1: %d, size2: %d\n", mc_rr, mc_rrr, i, j, info->size1, info->size2);
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
	if (info->best_val < info->s1_min)
		info->s1_min = info->best_val;
	else if (info->best_val > info->s1_max)
		info->s1_max = info->best_val;
	ft_printf("method: %d, val: %d, rot1: %d, rot2: %d, count: %d, size2: %d\n", info->best_method, info->best_val, info->rotate_1, info->rotate_2, info->best_count, info->size2);
}

void	sort_b(int *stack1, int *stack2, t_info *info)
{
	int	i;
	
	i = 0;
	info->s1_min = stack1[0];
	info->s1_max = stack1[info->size1 - 1];
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
	}
	i = 0;
    while (stack1[i])
        ft_printf("%d ", stack1[i++]);
    i = 0;
    ft_printf("\n");
    while (stack2[i])
        ft_printf("%d ", stack2[i++]);
    ft_printf("\n");
	pause();
}

void	push_m1(int *stack1, int *stack2, t_info *info)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	info->previous_val = stack1[info->best_index];
	while (i++ < info->total && info->size1 > info->best_count)
	{
		j = -1;
		n = 0;
		info->current_val = info->previous_val;
		while (stack1[n] != info->current_val)
			n++;
		while (++j < info->size1)
		{
			if (info->current_val == stack1[0])
			{
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
}

void	newsort(int *stack1, int *stack2, int *sorted, t_info *info)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	info->best_count = 0;
	info->best_method = 0;
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
	/*else if (info->best_method == 2)
		push_m2(stack1, stack2, sorted, info);*/
}

/*void    newsort(int *stack1, int *stack2, int *sorted, t_info *info)
{
    int i;
    int x;

    i = 0;
    x = 0;
    info->currentdiv += info->div;
    while (i++ < info->size1 && info->size1 > 3)
    {
        if (stack1[0] <= sorted[info->currentdiv])
        {
            ft_printf("pb\n");
		    push_to(stack1, stack2, info->size1--, info->size2++);
            i--;
            x++;
        }
        else
            stack_rotate(stack1, info->size1, 1, "ra\n");
    }
    info->div = info->div / 2;
    if (check_sorted(stack1, info->size1, 1) != 1 && info->size1 == 3)
		sort3(stack1);
    if (info->size1 > 3 && check_sorted(stack1, info->size1, 1) != 1)
        newsort(stack1, stack2, sorted, info);
    i = 0;
    while (stack1[i])
        ft_printf("%d ", stack1[i++]);
    i = 0;
    ft_printf("\n");
    while (stack2[i])
        ft_printf("%d ", stack2[i++]);
    ft_printf("\n");
    info->newdiv = x;
	sortb(stack1, stack2, sorted, info);
}*/
