/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:05:53 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/27 16:46:13 by lrondia          ###   ########.fr       */
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
	data->shlvl = 0;
	data->s_quote = 0;
	data->d_quote = 0;
	data->commands = NULL;
	data->len_env = 0;
	data->new_env = NULL;
	data->error_code = 0;
	g_ret_number = 0;
	init_env(data, &data->new_env, envp);
	increment_shell_level(data, data->new_env);
}
