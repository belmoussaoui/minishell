/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/02 19:01:02 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	t_data data;
	char	*line;
	while (19)
	{
		line = readline("minishell$ ");
		add_history(line);
		//printf("%s\n", line);
		ft_split(" ", *line);
		printf("%zu\n", ft_strlen(line));
		data.paths = path_finder(envp);
		data.path_cmd = ft_split(data.paths, ':');
		//printf("%s\n", path_cmd);

		data.args = ft_split(line, ' ');
		// printf("%s\n", line);
		// printf("Before\n");
		data.cmd = cmd_ok(data.path_cmd, data.args[0]);
		printf("%s\n", data.cmd);
		if (!data.cmd)
		{
			printf("Command not found\n");
		}
		execve(data.cmd, data.args, envp);
	}
	return (1);
}
