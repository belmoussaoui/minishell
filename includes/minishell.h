/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/22 15:28:06 by mliban-s         ###   ########.fr       */
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
# include "../libft/libft.h"

# define BUFF_SIZE 4096

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
	void	*data;
	t_list	*commands;
}	t_data;

typedef struct s_cmd
{
	char	**elements;
	int		infile;	
	int		outfile;
	void	*data;
}	t_cmd;

int	g_ret_number;

void	write_error(char *message, int code);

void	initializer(t_data *data, char *envp[]);

char	*reader(t_data *data);

int		syntax_error(t_data *data);

int		parser(t_data *data, t_list **commands, char *line);
void	redirections(t_data *data, t_list *commands);
void	handle_heredoc(t_data *data, t_cmd *cmd, char *stop);
char	*get_file(char *line);

void	expander(t_data *data, t_list *commands);

void	execute(t_data *data, char *envp[]);
void	run_builtin(t_data *data, char *cmd_name);
int		is_builtin(char *cmd_name);
int		cmp_env(t_data *data, t_list **new_env, int arg_count);
char	*get_env(t_list *env, char *name);

void	clear(t_data *data, char *line);

int		ft_pwd(void);

void	ft_unset(t_data *data, t_list **new_env);

void	ft_export(t_data *data, t_list **new_env);
void	parsing_export_unset(t_data *data, char *line);

void	ft_env(t_list *env);

void	increment_shell_level(t_data *data);

int		ft_atoi_1(const char *str);

bool	ft_cd(t_data *data);

bool	ft_echo(t_data *data);

void	clear_redirection(char **elements);

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

#endif