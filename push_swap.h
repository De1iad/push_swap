/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:51:03 by obibby            #+#    #+#             */
/*   Updated: 2022/08/07 19:15:45 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>

typedef struct s_info {
	int	size1;
	int	size2;
	int	max1;
	int	max2;
	int	min1;
	int	min2;
	int	total;
	int	start_val;
	int	current_val;
	int	previous_val;
	int	current_index;
	int	best_method;
	int	best_index;
	int	best_count;
	int	best_val;
	int	rotate_1;
	int	rotate_2;
}	t_info;

void	init_struct(t_info *info, int argc);
int		smallsort(int *stack1, int *stack2, t_info *info);
void	sort_rem(int *stack1, int *stack2, t_info *info);
int		push_to(int *src, int *dest, int ssize, int dsize);
void	stack_rotate(int *stack, int size, int dir, char *str);
void	swap(int *stack, char *str);
int		find_min(int *stack, int size);
int		find_max(int *stack, int size);
int		checkinput(char **argv, int s);
void	swap_both(int *stack1, int *stack2);
void	stack_shift(int *stack, int size, int dir);
int		sort3(int *stack1);
void    largesort(int *stack1, int *stack2, int *sorted, t_info *info);
void	rotate_to_order(int *stack1, t_info *info);
void	sort_b(int *stack1, int *stack2, t_info *info);

#endif