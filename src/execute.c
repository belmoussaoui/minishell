/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/15 19:34:28 by hakermad         ###   ########.fr       */
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

int	is_builtin(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "unset", 6) || !ft_strncmp(cmd_name, "export", 7));
}

void	redirecting(t_data *data, char *cmd_name, char *envp[])
{
	if (!ft_strncmp(cmd_name, "unset", 6))
		ft_unset(data, envp);
	else if (!ft_strncmp(cmd_name, "export", 7))
		ft_export(data, &data->new_env);
}

void	run_child(t_data *data, char *envp[], t_list *current)
{
	char	*path_temp;
	
	path_temp = path_finder(data, envp);
	data->paths = ft_split(path_temp, ':');
	data->elements = ((t_cmd *)(current->content))->elements;
	if (is_builtin(data->elements[0]))
		redirecting(data, data->elements[0], envp);
	else
	{	
		data->cmd = cmd_ok(data, data->paths, data->elements[0], envp);
		if (!data->cmd)
			werror_exit(data, "command not found", 127);
		if (current != data->commands)
			dup2(((t_cmd *)(current->content))->infile, STDIN_FILENO);
		if (ft_lstlen(current) > 1)
			dup2(((t_cmd *)(current->next->content))->outfile, STDOUT_FILENO);
		ft_close(current);
		execve(data->cmd, data->elements, envp);
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
}
// ! WEXITSTATUS
