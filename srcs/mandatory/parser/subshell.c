/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:51:12 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/17 22:41:47 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"
#include	"../../../libft/libft.h"

void	branch_subshell(t_node *p, bool *failed_flag)
{
	p->end_pos++;
	p->start_pos = p->end_pos;
	p->left = talloc(COMMAND_LINE, p);
	do_parse(p->left, failed_flag);
}

t_list	**traverse_subshell(t_node *p)
{
	t_list	**subshell;
	t_list	*shell;
	t_list	*list_ptr;
	t_list	**list;
	size_t	i;

	list = NULL;
	subshell = traverse(p->left);
	shell = subshell[0];
	i = 1;
	while (subshell[i] != NULL)
	{
		ft_lstadd_back(&shell, subshell[i]);
		i++;
	}
	list_ptr = ft_lstnew(make_command(SUBSHELL, NULL, NULL, shell));
	list = realloc_list_free(list, list_ptr);
	return (list);
	// ft_lstclear(&list_ptr, free); // kari
}
