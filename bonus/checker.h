/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:47:53 by obibby            #+#    #+#             */
/*   Updated: 2022/08/13 10:51:10 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_info {
	int	size[2];
	int	total;
	int	*stack[2];
}	t_info;

void	push_to(int *stack1, int *stack2, t_info *d, int dir);
void	swap(int *stack, t_info *d, int id);
void	swap_both(int *stack1, int *stack2, t_info *d);
void	stack_rotate(t_info *d, int s_id, int dir);
void	rotate_both(int dir, t_info *d);
int		check_input(char **argv, int s);
void	error_exit(int *stack1, int *stack2, int id);
void	check_sorted(int *stack1, int *stack2, t_info *d);
void	read_commands(int *stack1, int *stack2, t_info *d, int i);

#endif