/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:52:55 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/17 11:55:42 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list *env)
{
	while (env)
	{
		//incr_shlvl(env);
		printf("%s\n", env->content);
		env = env->next;
	}
}

void	shlvl_init(char *str)
{
	int	shlvl_init;

	shlvl_init = ft_itoa(str);
	if (shlvl_init < 0)
		return (0);
	else
		return (shlvl_init + 1);
}

void shlvl_incr(t_data *data, t_list **new_env)
{
	char	*shlvl_str;
	int		arg_count;
	
	arg_count = 1;
		while (*new_env)
	{
		shlvl_str = cmp_env(data, new_env, arg_count);
		if (!ft_strncmp("SHLVL", new_env, 6))
		{
			
			printf("SHLVL\n");
		}
	}
}