/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:56:08 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/28 21:28:50 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	*str;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)vars;
	while (true)
	{
		str = read_line_from_prompt();
		if (!str)
			continue ;
		free(str);
	}
	return (0);
}
