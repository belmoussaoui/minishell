/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/24 16:11:01 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
#include <termios.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		error_code;
	bool	s_quote;
	bool	d_quote;
	int		len_env;
	t_list	*new_env;
	char	*line;
	char	*cmd;
	char	**paths;
	char	**elements;
	t_list	*commands;
}	t_data;

typedef struct s_cmd
{
	char	**elements;
	int		infile;	
	int		outfile;
}	t_cmd;

int	g_ret_number;

// INIT
void	initializer(t_data *data, char *envp[]);
char	*reader(t_data *data);

// PARSING
int		syntax_error(t_data *data);
int		parser(t_data *data, t_list **commands, char *line);

// REDIRECTIONS
void	redirections(t_data *data, t_list *commands);
void	clear_redirection(char **elements);
void	handle_heredoc(t_data *data, t_cmd *cmd, char *stop);
void	handle_infile(t_data *data, t_cmd *cmd, char *infile);
void	handle_outfile(t_data *data, t_cmd *cmd, char *outfile);
void	handle_outfile_append(t_data *data, t_cmd *cmd, char *outfile);

// EXPANDER
void	expander(t_data *data, t_list *commands);

// EXECUTION
void	execute(t_data *data, char *envp[]);
void	run_builtin(t_data *data, char *cmd_name);
int		is_builtin(char *cmd_name);
int		cmp_env(t_data *data, t_list **new_env, int arg_count);
char	*get_env(t_list *env, char *name);

// BUILTINS
void	ft_env(t_list *env);

bool	ft_cd(t_data *data);

int		ft_pwd(void);

void	ft_unset(t_data *data, t_list **new_env);

void	ft_export(t_data *data, t_list **new_env);
void	parsing_export_unset(t_data *data, char *line);

void	increment_shell_level(t_list *new_env);
int		ft_atoi_shlvl(const char *str);

bool	ft_echo(t_data *data);

// CLEAR
void	clear(t_data *data);
void	*free_split(char **strings);

void	ft_exit(void);

void	run_fork(t_data *data, char *envp[], t_list *current);

// UTILS

int		is_metachar(char c);
int		check_quote(t_data *data, char c);
void	clear_quote(t_data *data);
void	ft_close(t_list *commands);
void	werror(t_data *data, char *message, int code);
void	werror_exit(t_data *data, char *message, int code);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split_quote(t_data *data, char const *s, char c);
char	**ft_split_redirections(t_data *data, char **s);
int		is_parent_cmd(char *cmd_name);

// DEBUG

void	debug_list(t_list *commands);
void	debug_env(t_list *env);
void	debug_split(char **split);

// SIGNAL
void	run_signals(int sig);
void	restore_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);
void	rl_replace_line(const char *text, int clear_undo);
void	term_config(void);

#endif