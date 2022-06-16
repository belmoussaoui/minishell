/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/16 14:17:54 by bel-mous         ###   ########.fr       */
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

char	*cmd_ok(t_data *data, char **paths, char *cmd_name, char *envp[])
{
	char	*temp;
	char	*command;

	if (!paths)
		return (NULL);
	if (ft_strncmp(data->line, "unset", 6) == 0)
	{
		ft_unset(data, envp);
	}
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
	char	*path_temp;

	path_temp = path_finder(data, envp);
	data->paths = ft_split(path_temp, ':');
	data->elements = ((t_cmd *)(current->content))->elements;
	data->cmd = cmd_ok(data, data->paths, data->elements[0], envp);
	if (current != data->commands)
		dup2(((t_cmd *)(current->content))->infile, STDIN_FILENO);
	if (ft_lstlen(current) > 1)
		dup2(((t_cmd *)(current->next->content))->outfile, STDOUT_FILENO);
	ft_close(current);
	if (is_builtin(data->elements[0]))
		run_builtin(data, data->elements[0], envp);
	else
	{
		if (!data->cmd)
			werror_exit(data, "command not found", 127);
		if (execve(data->cmd, data->elements, envp) == -1)
			werror_exit(data, "can't execve, error occured\n", 256);
	}
}

// Execute the list of commands.
void	execute(t_data *data, char *envp[])
{
	int		pid;
	t_list	*current;

	current = data->commands;
	while (current)
	{
		pid = fork();
		if (pid == -1)
			werror_exit(data, "can't fork, error occured\n", 127);
		else if (pid == 0)
			run_child(data, envp, current);
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
