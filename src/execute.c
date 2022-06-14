/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/14 12:29:10 by bel-mous         ###   ########.fr       */
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

void	run_child(t_data *data, char *envp[], int i)
{
	data->paths = path_finder(data, envp);
	data->path_cmd = ft_split(data->paths, ':');
	data->args = ((t_cmd *)(ft_lstget(data->commands, i)->content))->elements;
	data->cmd = cmd_ok(data->path_cmd, data->args[0]);
	if (!data->cmd)
		werror_exit(data, "command not found", 127);
	execve(data->cmd, data->args, envp);
}

// Execute the list of commands.
void	execute(t_data *data, char *envp[])
{
	pid_t	*pids;
	int		cmdn;
	int		i;

	cmdn = ft_lstlen(data->commands);
	pids = malloc(sizeof(int) * cmdn);
	if (!pids)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < cmdn)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			werror_exit(data, "can't fork, error occured\n", 127);
		else if (pids[i] == 0)
			run_child(data, envp, i);
		i++;
	}
	i = 0;
	while (i++ < cmdn)
		waitpid(-1, NULL, 0);
}
