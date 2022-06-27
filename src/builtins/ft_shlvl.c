/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:40:24 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/27 20:47:40 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	env_value_len(const char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	return (i);
}

void	increment_shell_level(t_data *data, t_list *new_env)
{
	char	*env_name;
	char	*shlvl;
	char	*shell_level_value;

	env_name = malloc(sizeof(char *) * env_value_len("SHLVL="));
	if (!env_name)
		exit (EXIT_FAILURE);
	shell_level_value = get_env(new_env, "SHLVL");
	if (ft_strncmp(shell_level_value, "", ft_strlen(shell_level_value)) == 0)
		return ;
	data->shlvl = ft_atoi_shlvl(shell_level_value) + 1;
	while (new_env->next)
	{
		get_env_name(env_name, new_env->content);
		if (ft_strncmp("SHLVL", env_name, 6) == 0)
		{
			shlvl = ft_itoa(data->shlvl);
			new_env->content = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			break ;
		}
		new_env = new_env->next;
	}
	free (env_name);
}
