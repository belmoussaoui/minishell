/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/29 16:31:18 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_pipe(t_data *data, t_list *current)
{
	t_cmd	*content;

	content = (t_cmd *)(current->content);
	if (current != data->commands && content->is_redirection != 0)
		dup2(content->infile, STDIN_FILENO);
	else if (content->is_redirection == 0)
		dup2(content->fd_redirection, STDIN_FILENO);
	if (ft_lstlen(current) > 1 && content->is_redirection != 1)
		dup2(((t_cmd *)(current->next->content))->outfile, STDOUT_FILENO);
	else if (content->is_redirection == 1)
		dup2(content->fd_redirection, STDOUT_FILENO);
	ft_close(current);
}

void	run_child(t_data *data, char **env, t_list *current)
{
	data->elements = ((t_cmd *)(current->content))->elements;
	dup_pipe(data, current);
	if (is_builtin(data->elements[0]))
	{
		run_builtin(data, data->elements[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		data->paths = ft_split(path_finder(env), ':');
		data->cmd = cmd_ok(data->paths, data->elements[0]);
		if (!data->cmd)
			werror_exit("command not found", 127);
		if (execve(data->cmd, data->elements, env) == -1)
			werror_exit("can't execve, error occured", 126);
	}
}

void	run_fork(t_data *data, t_list *current)
{
	int		pid;
	char	**env_tab;

	env_tab = env_list_to_tab(data->new_env);
	pid = fork();
	if (pid == -1)
		werror_exit("can't fork, error occured", 127);
	else if (pid == 0)
		run_child(data, env_tab, current);
}

void	end_execute(t_data *data)
{
	t_list	*current;

	current = data->commands;
	while (current)
	{
		wait(&g_error_code);
		current = current->next;
	}
	if (WIFEXITED(g_error_code))
		g_error_code = WEXITSTATUS(g_error_code);
	else if (WIFSIGNALED(g_error_code))
	{
		g_error_code = WTERMSIG(g_error_code);
		if (g_error_code != 131)
			g_error_code += 128;
	}
}

// Execute the list of commands.
void	execute(t_data *data)
{
	t_list	*commands;

	commands = data->commands;
	while (commands)
	{
		data->elements = ((t_cmd *)(commands->content))->elements;
		if (!data->elements[0])
			break ;
		if (!is_parent_cmd(data->elements[0]))
		{
			run_signals(2);
			run_fork(data, commands);
		}
		else if (ft_lstlen(data->commands) == 1)
			run_builtin(data, data->elements[0]);
		close(((t_cmd *)(commands->content))->infile);
		close(((t_cmd *)(commands->content))->outfile);
		commands = commands->next;
	}
	end_execute(data);
}
