/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:45:10 by mliban-s          #+#    #+#             */
/*   Updated: 2022/06/16 17:42:21 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, t_list **new_env)
{
	int		i;
	int		arg_count;
	char	*new_elem;

	arg_count = 1;
	while (data->elements[arg_count])
	{
		i = cmp_env(data, new_env);
		if (i == data->len_env)
		{
			ft_lstadd_back(new_env, ft_lstnew(data->elements[arg_count]));
			data->len_env++;
		}
		else
		{
			new_elem = ft_strdup(data->elements[arg_count]);
			(ft_lstget(*new_env, i))->content = new_elem;
		}
		arg_count++;
	}
}
	// debug_env(*new_env);
