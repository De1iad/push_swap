/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:51:03 by obibby            #+#    #+#             */
/*   Updated: 2022/08/10 23:53:31 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>

typedef struct s_info {
	int	size[3];
	int	max1;
	int	max2;
	int	min1;
	int	min2;
	int	trial;
	int	use_swap;
	int	m_count[8];
	int	total;
	int	start_val;
	int	current_val;
	int	previous_val;
	int	final_val;
	int	current_index;
	int	best_method;
	int	best_index;
	int	best_count;
	int	best_count2;
	int	coord_next;
	int	dir_next;
	int	val_next;
	int ra;
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
	int	best_val;
	int	rotate_1;
	int	rotate_2;
	int *stack[3];
}	t_info;

void	init_struct(t_info *info, int argc, int *stack1, int *stack2);
int		smallsort(int *stack1, int *stack2, t_info *info);
void	sort_rem(int *stack1, int *stack2, t_info *info);
int		push_to(int *stack1, int *stack2, t_info *info, int dir);
void	stack_rotate(t_info *info, int s_id, int dir, char *str);
void	swap(int *stack, t_info *info, char *str);
int		find_min(int *stack, int size);
int		find_max(int *stack, int size);
int		checkinput(char **argv, int s);
void	swap_both(int *stack1, int *stack2, t_info *info);
void	stack_shift(int *stack, int size, int dir);
int		sort3(int *stack1, t_info *info);
void	m1_begin(int *stack1, int *stack2, t_info *info);
void	m2_begin(int *stack1, int *stack2, int *sorted, t_info *info);
void	rotate_to_order(int *stack1, t_info *info);
void	sort_b(int *stack1, int *stack2, t_info *info);

#endif