/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:05:53 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/27 19:58:01 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data *data, t_list **new_env, char *envp[])
{
	int	i;

	i = 0;
	while (envp[data->len_env])
		data->len_env++;
	while (i < data->len_env)
	{
		ft_lstadd_back(new_env, ft_lstnew(envp[i]));
		i++;
	}
}

// Intialize minishell data and setup the environment.
void	initializer(t_data *data, char *envp[])
{
	data->s_quote = 0;
	data->d_quote = 0;
	data->commands = NULL;
	data->len_env = 0;
	data->new_env = NULL;
	g_error_code = 0;
	init_env(data, &data->new_env, envp);
	increment_shell_level(data->new_env);
}
