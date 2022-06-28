/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:14:12 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/28 20:17:22 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_x_error(char *command, char *message, int code)
{
	g_error_code = code;
	write(2, command, ft_strlen(command));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

char	*path_finder(char **envp)
{
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		werror_exit("No such file or directory", 127);
	return (*envp + 5);
}

char	*cmd_ok(char **paths, char *cmd_name)
{
	char	*temp;
	char	*command;

	if (!paths || !cmd_name[0])
		return (NULL);
	if (opendir(cmd_name))
		print_x_error(cmd_name, ": is a directory", 126);
	if (access(cmd_name, F_OK) == 0)
		return (cmd_name);
	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	if (cmd_name[0] == '/')
		print_x_error(cmd_name, ": No such file or directory", 127);
	return (NULL);
}

char	**env_list_to_tab(t_list *env)
{
	int		i;
	int		len;
	char	**env_tab;

	i = 0;
	len = ft_lstlen(env);
	env_tab = malloc(sizeof (char *) * len + 1);
	if (!env_tab)
		exit (EXIT_FAILURE);
	while (i < len)
	{
		env_tab[i] = malloc(sizeof(char)
				* ft_strlen((char *)(env->content)) + 1);
		if (!env_tab[i])
			exit (EXIT_FAILURE);
		ft_strlcpy(env_tab[i], (char *)(env->content),
			ft_strlen((char *)(env->content)) + 1);
		env = env->next;
		i++;
	}
	env_tab[i] = 0;
	return (env_tab);
}
