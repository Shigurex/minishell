/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_brank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:54:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/18 20:47:06 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide.h"

char	**delete_brank(char **array)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (array[i] != NULL)
	{
		if (array[i][0] == '\0' || ft_strcmp(array[i], "\"\"") == 0 || ft_strcmp(array[i], "\'\'") == 0)
		{
			j = i;
			while (1)
			{
				array[j] = array[j + 1];
				if (array[j + 1] == NULL)
					break ;
				j++;
			}
			continue ;
		}
		i++;
	}
	return (array);
}
