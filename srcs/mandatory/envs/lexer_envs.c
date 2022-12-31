/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:55:12 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:46:07 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"envs.h"

char	*check_env_value(t_vars *vars, char *env)
{
	t_list	*list;
	t_envs	*envs;
	char	*value;

	list = find_envs(vars->envs, env);
	if (!list)
		return ("");
	envs = (t_envs *)list->content;
	value = ft_strdup(envs->value);
	free(env);
	return (value);
}

char	*handle_env(t_vars *vars, char *line, size_t *pos)
{
	size_t	start;
	char	*env;

	if (ft_isdigit(line[*pos]))
	{
		(*pos)++;
		start = *pos;
		while (ft_isalnum(line[*pos]) || line[*pos] == '_')
			(*pos)++;
		return (substr_size_t(line, start, (*pos) - start));
	}
	start = (*pos);
	while (ft_isalnum(line[*pos]) || line[*pos] == '_')
		(*pos)++;
	env = substr_size_t(line, start, (*pos) - start);
	if (env == NULL)
		return (NULL);
	return (check_env_value(vars, env));
}

static char	*divide(t_vars *vars, char *line, size_t *pos, bool during[2])
{
	size_t	start;

	if (line[(*pos)] == '$' && (during[SQ] == false || during[DQ] == true))
	{
		(*pos)++;
		if (ft_isalnum(line[*pos]) || line[*pos] == '_')
			return (handle_env(vars, line, pos));
		else if (line[*pos] == '?')
		{
			(*pos)++;
			return (ft_itoa(g_status % 256));
		}
		else
			(*pos)--;
	}
	start = *pos;
	while (line[*pos] == '$')
		(*pos)++;
	while (line[*pos] != '$' && line[*pos] != '\0')
	{
		(*pos)++;
		if (line[*pos] == SINGLEQ)
			(during[SQ]) = !(during[SQ]);
	}
	return (substr_size_t(line, start, (*pos) - start));
}

static void	init_lexenv(char **line, bool during[2], size_t *pos)
{
	*pos = 0;
	*line = ft_strdup("");
	if (line == NULL)
		exit (1);
	during[SQ] = false;
	during[DQ] = false;
}

char	*lexer_envs(t_vars *vars, char *line)
{
	char	*divided_line;
	char	*temp;
	size_t	pos;
	size_t	start;
	bool	during[2];

	init_lexenv(&divided_line, during, &pos);
	while (line[pos] != '\0')
	{
		if (line[pos] == SINGLEQ)
			during[SQ] = !during[SQ];
		if (line[pos] == DOUBLEQ)
			during[DQ] = !during[DQ];
		start = pos;
		temp = divide(vars, line, &pos, during);
		if (temp == NULL)
		{
			free(temp);
			return (NULL);
		}
		divided_line = ft_strjoin(divided_line, temp);
	}
	return (divided_line);
}
