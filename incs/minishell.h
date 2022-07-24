/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:30 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/24 00:13:08 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// enums
enum e_type
{
	PIPE,
	INF,
	OUTF,
	APPF,
	HRDOC,
	OTHER
};

//structures
typedef struct s_data
{
	t_cmd	*cmds;
	int		exit_code;
}				t_data;

typedef struct s_token
{
	char			*value;
	enum e_type		type;
	struct s_token	*next;
}				t_token;

typedef struct s_name
{
	char			*name;
	struct s_file	*next;
}				t_name;

typedef struct s_cmd
{
	char			*cmd;
	t_name			*infiles;
	t_name			*outfiles;
	int				output_mode;
	t_name			*heredoc;
	int				input;
	t_name			*args_lst;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

//global variable
t_data	g_data;

// prototypes
int		ft_perror(char *name, char *error);
int		check_quotes(char *line);
t_token	*get_pipe(char **line, t_token *token);
char	*ft_strndup(const char *s1, size_t size);

// errors
# define QUOTES "syntax error: unclosed quotes"
# define UNXPCT "syntax error near unexpected token "

#endif
