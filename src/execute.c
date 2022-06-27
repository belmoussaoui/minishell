/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/22 17:56:32 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_finder(t_data *data, char **envp)
{
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		werror_exit(data, "No such file or directory", 127);
	return (*envp + 5);
}

char	*cmd_ok(char **paths, char *cmd_name)
{
	char	*temp;
	char	*command;

	if (!paths)
		return (NULL);
	if (access(cmd_name, F_OK) == 0)
		return (cmd_name);
	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	run_child(t_data *data, char *envp[], t_list *current)
{
	data->elements = ((t_cmd *)(current->content))->elements;
	dup2(((t_cmd *)(current->content))->infile, STDIN_FILENO);
	if (ft_lstlen(current) > 1)
		dup2(((t_cmd *)(current->next->content))->outfile, STDOUT_FILENO);
	ft_close(current);
	if (is_builtin(data->elements[0]))
	{
		run_builtin(data, data->elements[0]);
		exit(1);
	}
	else
	{
		data->paths = ft_split(path_finder(data, envp), ':');
		data->cmd = cmd_ok(data->paths, data->elements[0]);
		if (!data->cmd)
			werror_exit(data, "command not found", 127);
		if (execve(data->cmd, data->elements, envp) == -1)
			werror_exit(data, "can't execve, error occured\n", 256);
	}
}

void	run_fork(t_data *data, char *envp[], t_list *current)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		werror_exit(data, "can't fork, error occured\n", 127);
	else if (pid == 0)
		run_child(data, envp, current);
}

// Execute the list of commands.
void	execute(t_data *data, char *envp[])
{
	t_list	*current;

	current = data->commands;
	while (current)
	{
		data->elements = ((t_cmd *)(current->content))->elements;
		if (!is_parent_cmd(data->elements[0]))
		{
			run_signals(2);
			run_fork(data, envp, current);
		}
		else if (ft_lstlen(data->commands) == 1)
			run_builtin(data, data->elements[0]);
		close(((t_cmd *)(current->content))->infile);
		close(((t_cmd *)(current->content))->outfile);
		current = current->next;
	}
	current = data->commands;
	while (current)
	{
		wait(&data->error_code);
		current = current->next;
	}
	data->error_code = WEXITSTATUS(data->error_code);
}
