/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:30 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/10 20:02:21 by achahdan         ###   ########.fr       */
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

enum e_out_mode
{
	NEW,
	APP
};

enum e_input
{
	INFILE,
	HEREDOC,
	STDIN
};

//structures
typedef struct s_name
{
	char			*name;
	enum e_out_mode	out_mode;
	struct s_name	*next;
}				t_name;

typedef struct s_cmd
{
	char			*cmd;
	t_name			*infiles;
	t_name			*outfiles;
	t_name			*heredoc_lst;
	int				heredoc;
	enum e_input	input_source;
	t_name			*args_lst;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*value;
	enum e_type		type;
	struct s_token	*next;
}				t_token;

typedef struct s_data
{
	char	**env;
	t_env	*env_lst;
	t_cmd	*cmds;
	int		exit_code;
}				t_data;

//global variable
t_data	g_data;

// prototypes
int		ft_perror(char *name, char *error, int free);
int		check_quotes(char *line);
t_token	*get_pipe(char **line, t_token *token);
char	*ft_strndup(const char *s1, size_t size);
t_token	*make_token_lst(char *line);
t_token	*clear_token_lst(t_token *tokens);
int		check_malloc(void *to_be_checked, void *to_be_freed, int is_exit);
void	join_error_str(char *error1, char *token);
t_token	*get_other(char **line, t_token *token);
t_token	*get_pipe(char **line, t_token *token);
t_token	*get_outfile(char **line, t_token *token);
t_token	*get_input(char **line, t_token *token);
void	mv_2_nxt_quote(char *line, int *i);
int		parse_line(char *line);
int		check_name(char **line, t_token *token);
void	init_env_lst(char **env);
void	*ft_malloc(size_t count, size_t size, int is_exit);
int		ft_expand(t_token *token);
int		ft_strcmp(char *s1, char *s2);
void	check_n_expand(char *value, char *new, int *i, int *j);
int		ft_expand(t_token *token);
void	remove_quotes(char *value);
void	ft_add_history(char *line);
int		add_name(t_name **name_lst, t_token *token);
void	clear_names_lst(t_name *name_lst);
int		clear_cmds_lst(t_cmd *cmds);
int		args_lst_to_arr(t_cmd **cmd);

//miscellaneous defines
# define PROMPT  "MINISHELL$> "

// errors
# define QUOTES "syntax error: unclosed quotes"
# define UNXPCT "syntax error near unexpected token \'"

// BUILTINS
// -> export : 
t_env	*clone_list(void);
void	find_smallest(t_env *env);
void	print_in(void);
int		check_naming(char *str);
int		search_var(t_env *env, const char *var);

#endif
