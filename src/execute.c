/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/13 12:26:59 by lrondia          ###   ########.fr       */
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

char	*cmd_ok(char **paths, char *cmd)
{
	char	*temp;
	char	*command;

	if (!paths)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

// Execute the list of commands.
void	execute(t_data *data, char *line, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		werror_exit(data, "can't fork, error occured\n", 127);
	else if (pid == 0)
	{
		data->paths = path_finder(data, envp);
		data->path_cmd = ft_split(data->paths, ':');
		data->args = ft_split(line, ' ');
		data->cmd = cmd_ok(data->path_cmd, data->args[0]);
		if (!data->cmd)
			werror_exit(data, "command not found", 127);
		execve(data->cmd, data->args, envp);
	}
	waitpid(-1, NULL, 0);
}
