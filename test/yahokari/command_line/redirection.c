/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:36:05 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/23 20:28:21 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"

void	exec_lt(t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	fd = open(order->file, O_RDONLY);
	if (fd == ERR)
		exit(EXIT_FAILURE);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	next_order = (t_order *)next_piped_commands->content;
	if (next_order->read_fd != NONE)
		close(next_order->read_fd);
	next_order->read_fd = fd;
}

void	exec_gt(t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	fd = open(order->file, O_WRONLY | O_CREAT | 0644);
	if (fd == ERR)
		exit(EXIT_FAILURE);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	next_order = (t_order *)next_piped_commands->content;
	if (next_order->write_fd != NONE)
		close(next_order->write_fd);
	next_order->write_fd = fd;
}

void	exec_gtgt(t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	fd = open(order->file, O_WRONLY | O_CREAT | O_APPEND | 0644);
	if (fd == ERR)
		exit(EXIT_FAILURE);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	next_order = (t_order *)next_piped_commands->content;
	if (next_order->write_fd != NONE)
		close(next_order->write_fd);
	next_order->write_fd = fd;
}