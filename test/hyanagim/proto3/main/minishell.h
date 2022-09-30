/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:23:58 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 21:20:11 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<stdbool.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../../../../libft/libft.h"

# define READ 0
# define WRITE 1

// PIPE "/"
// AND "&&"
// OR "||"

// typedef enum e_type {
// 	COMMAND,
// 	SHELL,
// 	PIPE,
// 	AND,
// 	OR
// }	t_type;

typedef enum e_type {
	COMMAND_LINE,
	PIPED_LINE,
	PIPE,
	DELIMITER,
	ARGUMENTS,
	REDIRECTION,
	STRING,
	EXPANDABLE,
	NOT_EXPANDABLE,
	EXPANDABLE_QUOTED,
	SUBSHELL,
	LT,
	GT,
	GTGT,
	LTLT,
	COMMAND,
	AND,
	OR
}	t_type;

// typedef struct s_pipe_fd {
// 	int	read_fd;
// 	int	write_fd;
// 	int	next_read_fd;
// }	t_pipe_fd;


// typedef struct s_comline {
// 	t_type	type;
// 	char	**cmd;
// 	//パイプなどで繋がれたコマンドをダブルポインタで表示
// 	// t_type == COMMAND -> cmd = {"cat Makefile", "wc -l", "NULL"}
// 	// t_type != COMMAND -> cmd = NULL
// 	t_list	*shell;
// 	//sub shellの最初のコマンドのポインタを設定
// 	// t_type == SHELL -> shell = &t_command_line
// 	// t_type != SHELL -> shell = NULL
// 	// struct s_command_line	*next;
// }	t_comline;

// typedef struct s_vars {
// 	t_tree	*tree;
// 	int		lexer_size;
// 	int		lexer_pos;
// }	t_vars;


# include	<stddef.h>
typedef struct s_split
{
	char	*line;
	size_t	pos;
	size_t	size;
	size_t	dquote;
	size_t	squote;
	size_t	*length;
	char	**array;
}	t_array;


typedef struct s_node
{
	t_type			type;
	char			**line;
	int				*ele_is_quoted;
	size_t			*ele_length;
	size_t			array_size;
	size_t			start_pos;
	size_t			current_pos;
	size_t			end_pos;
	bool			include_right;
	size_t			index;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_order {
	t_type	type;
	char	**cmd;
	int		read_fd;
	int		write_fd;
	int		next_read_fd;
	char	*file;
	t_list	*shell;
}	t_order;

char	**lx_split(char *s, char c);
int		print_error(const char *message);
t_array	*lexer(t_array	*data);
#endif

// void		execute_shell(t_list *list);
// t_comline	*make_command(t_type type, char **cmd, t_list *shell);
// size_t		count_pipes(t_list *shell);
// void		display_command(t_list	*command_line);

//typedef enum e_com_type {
//	CD,
//	MKDIR,
//	LS
//}	t_com_type;

//typedef struct s_command {
//	t_com_type	type;
//	char		*buf;
//	char		*command;
//	char		*option;
//	int			has_opt;
//}	t_command;

// #endif
// #ifndef MINISHELL_H
// # define MINISHELL_H

// # include	<unistd.h>
// # include	<stdio.h>
// # include	<stdlib.h>
// # include	<string.h>
// # include	<readline/readline.h>
// # include	<readline/history.h>
// # include	"../parser/parser.h"

// # define TRUE 1
// # define FALSE 0

// typedef struct s_vars {
// 	t_tree	*tree;
// 	int		lexer_size;
// 	int		lexer_pos;
// }	t_vars;

//typedef enum e_type {
//	PIPE,
//	COMMAND
//}	t_type;

//typedef enum e_com_type {
//	CD,
//	MKDIR,
//	LS
//}	t_com_type;

//typedef struct s_command {
//	t_com_type	type;
//	char		*buf;
//	char		*command;
//	char		*option;
//	int			has_opt;
//}	t_command;

// #endif