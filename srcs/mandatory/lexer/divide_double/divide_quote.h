/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_quote.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:59:21 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/19 13:05:30 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDE_QUOTE_H
# define DIVIDE_QUOTE_H

# include "../../../../libft/libft.h"
# include "../../../../include/minishell.h"
// # include "../../lexer/lexer.h"
// # include "structure.h"

# define DUBLEQ '"'
# define SINGLEQ '\''

bool	check_line_re(char *line);
void	split_line_re(t_array *data, int type);
t_array	*malloc_element_re(t_array *data);
t_array	*malloc_array_re(t_array *data);
char	**lexer_re(t_array	*data);
bool	is_separator_re(char c, char d);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
void	free_array(t_array *data);
bool	is_ltltgtgt(char c, char d);
bool	is_null(char c);
char	**divide_redirect(char **array);
bool	push_element_quo(t_array *data, size_t i, size_t len, int type);
bool	push_element_re(t_array *data, size_t *i, size_t *len, int type);
#endif