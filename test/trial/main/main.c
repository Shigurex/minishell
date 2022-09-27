/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:10:45 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 21:20:36 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

t_order	*make_command(t_type type, char **cmd, char *file, t_list *shell)
{
	t_order	*command_line;

	command_line = malloc(sizeof(t_order));
	command_line->type = type;
	if (type == COMMAND)
		command_line->cmd = cmd;
	else
		command_line->cmd = NULL;
	if (type == GTGT || type == GT || type == LTLT || type == LT)
		command_line->file = file;
	else
		command_line->file = NULL;
	command_line->pipe_num = -1;
	command_line->read_fd = -1;
	command_line->write_fd = -1;
	command_line->next_read_fd = -1;
	if (type == SUBSHELL)
		command_line->shell = shell;
	else
		command_line->shell = NULL;
	return (command_line);
}

// size_t	count_pipes(t_list *shell)
// {
// 	size_t		count;
// 	t_list		*buf;
// 	t_comline	*command_line;

// 	count = 0;
// 	buf = shell;
// 	while (buf)
// 	{
// 		command_line = (t_comline *)buf->content;
// 		if (command_line->type == PIPE)
// 			count++;
// 		else if (command_line->type == AND || command_line->type == OR)
// 			break ;
// 		buf = buf->next;
// 	}
// 	return (count);
// }

// void	delete_command(void *content)
// {
// 	t_comline	*command_line;

// 	command_line = (t_comline *)command_line;
// 	free(command_line);
// }

void	display_command(t_list *command_line)
{
	size_t	i;
	t_list	*buf;
	t_order	*command;

	buf = command_line;
	while (buf)
	{
		command = (t_order *)buf->content;
		if (command->type == COMMAND)
		{
			printf("type: [ %s ] command: [", "command");
			i = 0;
			while (command->cmd[i])
			{
				printf(" %s", command->cmd[i]);
				i++;
			}
			printf(" ]\n");
		}
		else if (command->type == SUBSHELL)
		{
			printf("type: [ %s ]\n", "shell");
			printf("---------- inside shell ----------\n");
			display_command(command->shell);
		}
		else if (command->type == PIPE)
			printf("type: [ %s ]\n", "pipe");
		else if (command->type == AND)
			printf("type: [ %s ]\n", "and");
		else if (command->type == OR)
			printf("type: [ %s ]\n", "or");
		buf = buf->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	t_list	*command_line;
	char	*str;

	(void)argc;
	(void)argv;
	vars.envs_list = NULL;
	convert_envp_to_list(&vars, envp);
	while (true)
	{
		str = exec_readline();
		check_comline(command_line);
		exec_comline(&vars, command_line);
		free(str);
		break ;
	}
}
