/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:59:21 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/29 21:59:13 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../../libft/libft.h"
# include "../../trial/main/main.h"
// # include "structure.h"

# define DUBLEQ '"'
# define SINGLEQ '\''

bool	check_line(char *line);
void	split_line(t_array *data, int type);
t_array	*malloc_element(t_array *data);
t_array	*malloc_array(t_array *data);

#endif