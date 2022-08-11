/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:51:03 by obibby            #+#    #+#             */
/*   Updated: 2022/08/11 16:47:29 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>

typedef struct s_info {
	int	size[3];
	int	max1;
	int	min1;
	int	trial;
	int	use_swap;
	int	m_count[5];
	int	total;
	int	start_val;
	int	current_val;
	int	previous_val;
	int	current_index;
	int	best_method;
	int	best_index;
	int	best_count;
	int	best_count2;
	int	dir_next;
	int	count;
	int	swap;
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int	ra2;
	int	rb2;
	int	rra2;
	int	rrb2;
	int	i0;
	int	j0;
	int	swap_count;
	int	rotate_1;
	int	rotate_2;
	int	*stack[3];
}	t_info;

void	init_struct(t_info *d, int argc, int *stack1, int *stack2);
int		smallsort(int *stack1, int *stack2, t_info *d);
void	sort_rem(int *stack1, int *stack2, t_info *d);
int		push_to(int *stack1, int *stack2, t_info *d, int dir);
void	stack_rotate(t_info *d, int s_id, int dir, char *str);
void	swap(int *stack, t_info *d, char *str);
int		find_min(int *stack, int size);
int		find_max(int *stack, int size);
int		check_input(char **argv, int s);
void	swap_both(int *stack1, int *stack2, t_info *d);
void	stack_shift(int *stack, int size, int dir);
int		sort3(int *stack1, t_info *d);
void	m1_plan(int *stack1, int *stack2, t_info *d);
void	m2_plan(int *stack1, int *stack2, int *sorted, t_info *d);
void	rotate_to_order(int *stack1, t_info *d);
void	sort_b(int *stack1, int *stack2, t_info *d);
void	presort(int *stack, char **argv, int *sorted, int size);
void	init_vals(t_info *d, int argc);
int		sorted(int *stack, t_info *d);
void	check_path(int *stack1, t_info *d);

#endif