/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:00:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 21:15:48 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

#include	"../../../includes/debug.h"

void	do_parse(t_node *p, bool *failed_flag)
{
	if (p->type == COMMAND_LINE)
		branch_command_line(p, failed_flag);
	if (p->type == DELIMITER)
		branch_delimiter(p, failed_flag);
	if (p->type == PIPED_LINE)
		branch_piped_line(p, failed_flag);
	if (p->type == PIPE)
		branch_pipe(p, failed_flag);
	if (p->type == ARGUMENTS)
		branch_arguments(p, failed_flag);
	if (p->type == REDIRECTION)
	{
		p->current_pos = p->end_pos; //redirection
		p->end_pos++;
		if (p->line[p->end_pos] == NULL)
		{
			printf("%s\n", "error in redirection in do_parse");
			return ;
			//ここで，free
		}
		// printf("aim is %s\n", p->line[p->end_pos]);
		// p->end_pos++;
		// if (p->line[p->end_pos] != NULL)
		// {
		// 	p->start_pos = p->current_pos + 2;
		// 	p->end_pos = p->current_pos + 2;
		// 	// printf("204 %s\n", p->line[p->end_pos]);
		// 	p->right = talloc(COMMAND, p);
		// 	do_parse(p->right, failed_flag);
		// }
	}
	if (p->type == SUBSHELL)
	{
		p->end_pos++;
		p->start_pos = p->end_pos;
		p->left = talloc(COMMAND_LINE, p);
		do_parse(p->left, failed_flag);
	}
	return ;
}

//""を外した先頭のexpandableコマンドが全部アルファベットだったら，外していい
// リダイレクションとサブシェルの位置関係はいじれない


t_node	*talloc(t_type type, t_node *parent)
{
	t_node *p;
	p = malloc(sizeof(t_node));
	p->type = type;
	p->detail = parent->detail;
	p->line = parent->line;
	p->ele_is_quoted = parent->ele_is_quoted;
	p->ele_length = parent->ele_length;
	p->array_size = parent->array_size;
	p->start_pos = parent->start_pos;
	p->current_pos = parent->current_pos; //?????後で見る。
	p->end_pos = parent->end_pos;
	p->include_right = parent->include_right;
	p->index = parent->index + 1;
	p->parent =  parent;
	p->left = parent->left;
	p->right = parent->right;
	// node自体と，コマンドラインの分のmallocをする。
	// typeの代入と，コマンドのポインタの代入をする？（ポインタの複製。）
	// スタートポスとエンドポスの初期化をする。
	// 最初と最後は最初は一緒。
	return p;
}
// //talloc 失敗した時のエラー処理を後で書く

t_list **realloc_list(t_list **list, t_list *ptr)
{
	t_list	**new;
	size_t	size;
	size_t	i;

	size = 0;
	while (list[size] != NULL)
		size++;
	new = malloc(sizeof(t_list *) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = list[i];
		i++;
	}
	
	new[size] = ptr;
	new[size + 1] = NULL;
	// free(list);
	return (new);
}

t_type	convert_redirection(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (LT);
	if (ft_strcmp(str, ">") == 0)
		return (GT);
	if (ft_strcmp(str, ">>") == 0)
		return (GTGT);
	if (ft_strcmp(str, "<<") == 0)
		return (LTLT);
	return (COMMAND_LINE);
}

size_t	listlen(t_list **list)
{
	size_t	i;

	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

t_list	**listjoin(t_list **list, t_list **latter)
{
	size_t	length;
	size_t	i;
	size_t	j;
	t_list	**new;

	length = listlen(list) + listlen(latter) + 1;
	new = malloc(sizeof(t_list * ) * length);
	i = 0;
	while (list[i] != NULL)
	{
		new[i] = list[i];
		i++;
	}
	j = 0;
	while (latter[j] != NULL)
	{
		new[i + j] = latter[j];
		j++;
	}
	new[length] = NULL;
	return (new);
}

static void	comswap(t_list **list, size_t i, size_t j)
{
	t_list *temp;

	if (((t_order *)list[i]->content)->type > ((t_order *)list[j]->content)->type)
	{
		temp = list[i];
		list[i] = list[j];
		list[j] = temp;
	}
}

t_list	**sort_list(t_list	**list)
{
	size_t	i;
	size_t	j;

	i = listlen(list);
	while (i > 1)
	{	
		j = 0;
		while (j < i - 1)
		{
			comswap(list, j, j + 1);
			j++;
		}
		i--;
	}
	return (list);
}


t_list	**executer(t_node *p, t_list **list)
{
	if (p->type == COMMAND_LINE)
		list = executer(p->left, list);
	if (p->type == SUBSHELL)
	{
		t_list	**subshell;
		t_list	*shell;
		t_list	*list_ptr;
		size_t	i;

		subshell = executer(p->left, list);
		shell = subshell[0];
		i = 1;
		while (subshell[i] != NULL)
		{
			ft_lstadd_back(&shell, subshell[i]);
			i++;
		}
		
		list_ptr = ft_lstnew(make_command(SUBSHELL, NULL, NULL, shell));
		////////////ここで，listの中身調べる。
		list = realloc_list(list, list_ptr);
	}
	if (p->type == DELIMITER)
	{
		t_list	**latter;
		t_list	*list_ptr;

		if (p->detail == OR)
			list_ptr = ft_lstnew(make_command(OR, NULL, NULL, NULL));
		if (p->detail == AND)
			list_ptr = ft_lstnew(make_command(AND, NULL, NULL, NULL));
		list = executer(p->left, list);
		list = realloc_list(list, list_ptr);
		latter = malloc(sizeof(t_list *));
		latter[0] = NULL;
		latter = executer(p->right, latter);
		list = listjoin(list, latter);
	}
	if (p->type == PIPED_LINE)
		list = executer(p->left, list);
	if (p->type == PIPE)
	{
		t_list	**latter;
		t_list	*list_ptr;
		list_ptr = ft_lstnew(make_command(PIPE, NULL, NULL, NULL));
		list = executer(p->left, list);
		list = realloc_list(list, list_ptr);
	
		latter = malloc(sizeof(t_list *));
		latter[0] = NULL;
		latter = executer(p->right, latter);
		list = listjoin(list, latter);
	}
	if (p->type == ARGUMENTS)
	{
		list = executer(p->left, list);
		if (p->right != NULL)
			list = executer(p->right, list);
		if (p->parent->type == PIPE)
		{
			list = sort_list(list);
		}
		if (p->parent->type == PIPED_LINE)
		{
			list = sort_list(list);
		}
	}
	if (p->type == REDIRECTION)
	{
		t_list	*list_ptr;
		t_type	type;
		type = convert_redirection(p->line[p->current_pos]);
		list_ptr = ft_lstnew(make_command(type, NULL, p->line[p->current_pos + 1], NULL));
		list = realloc_list(list, list_ptr);
		/* int i = 0;
		while (list[i] != NULL && size  == 2)
		{
			printf("list point in comma %p\n", list[i]);
			printf("list type in comma %u\n", ((t_order *)list[i]->content)->type);
			if (((t_order *)list[i]->content)->type == COMMAND)
				printf("list cmd in comma %s\n", ((t_order *)list[i]->content)->cmd[0]);
			i++;
		} */
	}
	if (p->type == COMMAND)
	{
		char	**array;
		size_t	i;
		t_list	*list_ptr;
		while (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos]) && !is_bra(p->line[p->end_pos])
			&& !is_pipe(p->line[p->end_pos]) && !is_redirection(p->line[p->end_pos]))
			p->end_pos++;
		array = malloc(sizeof(char *) * (p->end_pos - p->start_pos + 1));
		if (array == NULL)
			; //後で書く。
		i = 0;
		while (i < p->end_pos - p->start_pos)
		{
			array[i] = ft_strdup(p->line[p->start_pos + i]);
			if (array[i] == NULL)
				; //後で書く。
			i++;
		}
		array[i] = NULL;
		list_ptr = ft_lstnew(make_command(COMMAND, array, NULL, NULL));
		list = realloc_list(list, list_ptr);
		// size_index(list, p, COMMAND);
	}

	return (list);
}
// //stringかなんかで，
// //p->left が NULL だったら，lstnew して，登りながら，lstadd していく。


void	listlcpy(t_list **dst, t_list **list, size_t dstsize)
{
	size_t	i;

	if (dstsize > 0)
	{
		i = 0;
		while (list[i] && i < dstsize - 1)
		{
			dst[i] = list[i];
			i++;
		}
		dst[i] = NULL;
	}
}

void	cmdjoin(t_list **list)
{
	size_t	i;

	i = 0;
	while (i < listlen(list) - 1)
	{
		if (((t_order *)list[i]->content)->type == COMMAND &&
			((t_order *)list[i + 1]->content)->type == COMMAND)
		{
			((t_order *)list[i]->content)->cmd = arrayjoin(((t_order *)list[i]->content)->cmd, ((t_order *)list[i + 1]->content)->cmd);
			listlcpy(&(list[i + 1]), &(list[i + 2]), listlen(list));
		}
		i++;
	}
}

void	init_root(t_node *root)
{
	root->type = COMMAND_LINE;
	root->array_size = 11;
	root->start_pos = 0;
	root->current_pos = 0;
	root->end_pos = 0;
	root->include_right = 0;
	root->index = 0;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
}

bool	check_array_redirect(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (check_arguments(array[i]) == false)
		{
			ft_putendl_fd("syntax error unexpected token", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

t_list	*parser(char **array)
{
	t_node	root;
	t_list	**list;
	t_list	*maked_list;
	bool	failed_flag;

	root.line = array;
	failed_flag = false;
	init_root(&root);
	
	if (check_array_redirect(array) == false)
		return (NULL);
	do_parse(&root, &failed_flag);
	if (failed_flag)
		return (NULL);
	list = malloc(sizeof(t_list *) * 1);
	list[0] = NULL;
	list = executer(&root, list);
	int i = 0;
	cmdjoin(list);
	maked_list = list[0];
	i = 1;
	while (list[i] != NULL)
	{
		ft_lstadd_back(&maked_list, list[i]);
		i++;
	}

	display_command(maked_list); //プリント
	return (maked_list);
}