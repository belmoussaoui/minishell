/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/06 16:40:39 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *data, char *line, char *envp[])
{
	pid_t	pid;

	data->paths = path_finder(envp);
	data->path_cmd = ft_split(data->paths, ':');
	data->args = ft_split(line, ' ');
	data->cmd = cmd_ok(data->path_cmd, data->args[0]);
	if (!data->cmd)
		printf("Command not found\n");
	pid = fork();
	if (pid == -1)
		printf("Error fork\n");
	else if (pid == 0)
		execve(data->cmd, data->args, envp);
	waitpid(-1, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	*line;

	(void) argc;
	(void) argv;
	while (19)
	{
		line = readline("minishell$ ");
		add_history(line);
		ft_split(" ", *line);
		exec(&data, line, envp);
	}
	return (1);
}
