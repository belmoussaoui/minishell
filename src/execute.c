/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/15 13:49:32 by lrondia          ###   ########.fr       */
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

void	run_child(t_data *data, char *envp[], t_list *current)
{
	data->paths = path_finder(data, envp);
	data->path_cmd = ft_split(data->paths, ':');
	data->args = ((t_cmd *)(current->content))->elements;
	data->cmd = cmd_ok(data->path_cmd, data->args[0]);
	if (!data->cmd)
		werror_exit(data, "command not found", 127);
	if (current != data->commands)
		dup2(((t_cmd *)(current->content))->infile, STDIN_FILENO);
	if (ft_lstlen(current) > 1)
		dup2(((t_cmd *)(current->next->content))->outfile, STDOUT_FILENO);
	ft_close(current);
	if (execve(data->cmd, data->args, envp) == -1)
		werror_exit(data, "can't execve, error occured\n", 256);
}
// code d'erreur pour échec d'execve ?

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
}
// ! WEXITSTATUS
