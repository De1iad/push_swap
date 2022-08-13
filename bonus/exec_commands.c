/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:58:58 by obibby            #+#    #+#             */
/*   Updated: 2022/08/13 13:31:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	exec_rotate(char *arr, int *stack1, int *stack2, t_info *d)
{
	if (arr[1] == 'a' && !arr[2])
		stack_rotate(d, 0, 1);
	else if (arr[1] == 'b' && !arr[2])
		stack_rotate(d, 1, 1);
	else if (arr[1] == 'r')
	{
		if (arr[2] == '\0')
			rotate_both(1, d);
		else if (arr[2] == 'a' && !arr[3])
			stack_rotate(d, 0, -1);
		else if (arr[2] == 'b' && !arr[3])
			stack_rotate(d, 1, -1);
		else if (arr[2] == 'r' && !arr[3])
			rotate_both(-1, d);
		else
			error_exit(stack1, stack2, 1);
	}
	else
		error_exit(stack1, stack2, 1);
}

void	exec_push(char *arr, int *stack1, int *stack2, t_info *d)
{
	if (arr[1] == 'a' && !arr[2])
		push_to(stack1, stack2, d, -1);
	else if (arr[1] == 'b' && !arr[2])
		push_to(stack1, stack2, d, 1);
	else
		error_exit(stack1, stack2, 1);
}

void	exec_swap(char *arr, int *stack1, int *stack2, t_info *d)
{
	if (arr[1] == 'a' && !arr[2])
		swap(stack1, d, 0);
	else if (arr[1] == 'b' && !arr[2])
		swap(stack2, d, 1);
	else if (arr[1] == 's' && !arr[2])
		swap_both(stack1, stack2, d);
	else
		error_exit(stack1, stack2, 1);
}

void	read_arr(char *arr, int *stack1, int *stack2, t_info *d)
{
	if (arr[0] == 'r')
		exec_rotate(arr, stack1, stack2, d);
	else if (arr[0] == 'p')
		exec_push(arr, stack1, stack2, d);
	else if (arr[0] == 's')
		exec_swap(arr, stack1, stack2, d);
	else
		error_exit(stack1, stack2, 1);
}

void	read_commands(int *stack1, int *stack2, t_info *d, int i)
{
	char	buffer;
	char	arr[4];

	while (read(STDIN_FILENO, &buffer, 1) == 1)
	{
		if (i == 0 && buffer != 'r' && buffer != 's' && buffer != 'p')
			error_exit(stack1, stack2, 1);
		else if (i == 1 && buffer != 'r' && buffer != 'b'
			&& buffer != 'a' && buffer != 's')
			error_exit(stack1, stack2, 1);
		else if (i == 2 && buffer != 'r' && buffer != 'a' && buffer != 'b'
			&& buffer != '\n')
			error_exit(stack1, stack2, 1);
		if ((i == 2 || i == 3) && buffer == '\n')
		{
			arr[i] = '\0';
			read_arr(arr, stack1, stack2, d);
			i = 0;
			continue ;
		}
		else if (i == 3 && buffer != '\n')
			error_exit(stack1, stack2, 1);
		arr[i++] = buffer;
	}
}
