/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:48:44 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 21:03:25 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include	"define.h"
# include	"../libft/libft.h"

bool	is_delimiter(char *str);
bool	check_line(char *line);
bool	is_separator(char c);
bool	check_arguments(char *str);
bool	is_bra(char *str);
bool	is_pipe(char *str);
bool	is_redirection(char *str);
void	split_line(t_array *data, int type);
t_array	*malloc_element(t_array *data);
t_array	*malloc_array(t_array *data);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
t_node	*talloc(t_type type, t_node *parent);
t_list	*parser(char **array);
void	match_bra(t_node *p);
void	do_parse(t_node *p, bool *failed_flag);
void	start_right(t_node *p);
void	start_left(t_node *p);
void	branch_command_line(t_node *p, bool *failed_flag);
void	branch_delimiter(t_node *p, bool *failed_flag);
void	branch_piped_line(t_node *p, bool *failed_flag);
void	branch_pipe(t_node *p, bool *failed_flag);
void	branch_arguments(t_node *p, bool *failed_flag);
void	branch_redirection(t_node *p, bool *failed_flag);
void	branch_subshell(t_node *p, bool *failed_flag);
#endif
