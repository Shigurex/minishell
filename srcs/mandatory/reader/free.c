/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:03:07 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 22:05:05 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

t_list	*free_line(char *line)
{
	free(line);
	return (NULL);
}