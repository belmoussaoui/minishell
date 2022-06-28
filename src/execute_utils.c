/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:14:12 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/28 19:24:43 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
