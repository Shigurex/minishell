/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:11:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/02 21:36:29 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide_quote.h"

bool	is_separator_re(char c, char d)
{
	if ((c == '<' && d == '<') || d == '\0')
		return (true);
	if ((c == '>' && d == '>') || d == '\0')
		return (true);
	return (false);
}