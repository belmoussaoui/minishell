/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:02:14 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/27 19:14:05 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child(t_data *data, char **env, t_list *current)
{
	t_cmd	*content;

	content = (t_cmd *)(current->content);
	data->elements = content->elements;
	if (current != data->commands)
		dup2(content->infile, STDIN_FILENO);
	if (ft_lstlen(current) > 1)
		dup2(((t_cmd *)(current->next->content))->outfile, STDOUT_FILENO);
	else if (content->is_redirection)
		dup2(content->outfile, STDOUT_FILENO);
	ft_close(current);
	if (is_builtin(data->elements[0]))
	{
		run_builtin(data, data->elements[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		data->paths = ft_split(path_finder(data, env), ':');
		data->cmd = cmd_ok(data->paths, data->elements[0]);
		if (!data->cmd)
			werror_exit(data, "command not found", 127);
		if (execve(data->cmd, data->elements, env) == -1)
			werror_exit(data, "can't execve, error occured\n", 126);
	}
}

void	run_fork(t_data *data, t_list *current)
{
	int		pid;
	char	**env_tab;
	env_tab = env_list_to_tab(data->new_env);
	pid = fork();
	if (pid == -1)
		werror_exit(data, "can't fork, error occured\n", 127);
	else if (pid == 0)
		run_child(data, env_tab, current);
}

// Execute the list of commands.
void	execute(t_data *data)
{
	t_list	*current;

	current = data->commands;
	while (current)
	{
		data->elements = ((t_cmd *)(current->content))->elements;
		if (!is_parent_cmd(data->elements[0]))
		{
			run_signals(2);
			run_fork(data, current);
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
