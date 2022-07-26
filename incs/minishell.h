/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:30 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/26 16:55:42 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

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

typedef struct s_data
{
	char	**env;
	t_cmd	*cmds;
	int		exit_code;
	char	*prompt;
}				t_data;

typedef struct s_token
{
	char			*value;
	enum e_type		type;
	struct s_token	*next;
}				t_token;

//global variable
t_data	g_data;

// prototypes
int		ft_perror(char *name, char *error, int free);
int		check_quotes(char *line);
t_token	*get_pipe(char **line, t_token *token);
char	*ft_strndup(const char *s1, size_t size);
t_token	*make_token_lst(char *line);
t_token	*clear_token_lst(t_token *tokens);
int		check_malloc(void *to_be_checked, void *to_be_freed);
void 	join_error_str(char *error1, char *token);
t_token	*get_other(char **line, t_token *token);
t_token	*get_pipe(char **line, t_token *token);
t_token	*get_outfile(char **line, t_token *token);
t_token	*get_input(char **line, t_token *token);
void	mv_2_nxt_quote(char *line, int *i);
int		parse_line(char *line);

//miscellaneous defines
# define PROMPT  "\x1b[32m" "minishell$ " "\x1b[0m"

// errors
# define QUOTES "syntax error: unclosed quotes"
# define UNXPCT "syntax error near unexpected token \'"

#endif
