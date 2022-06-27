/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:45:10 by mliban-s          #+#    #+#             */
/*   Updated: 2022/06/27 18:48:33 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_export_unset(char *line)
{
	int		i;
	char	c;

	i = 0;
	if (ft_isdigit(line[i]))
	{
		werror("export: not a valid identifier", 1);
		exit (1);
	}
	while (line[i])
	{
		c = line[i];
		if (!ft_isalnum(c) && c != '_' && c != ' ' && c != '\\'
			&& c != '"' && c != '\'' && c != '=')
		{
			werror("export: not a valid identifier", 1);
			exit (1);
		}
		i++;
	}
}

void	ft_export(t_data *data, t_list **new_env)
{
	int		i;
	int		arg_count;

	arg_count = 1;
	while (data->elements[arg_count])
	{
		parsing_export_unset(data->elements[arg_count]);
		i = cmp_env(data, new_env, arg_count);
		if (!ft_strchr(data->elements[arg_count], '='))
		{
			arg_count++;
			continue ;
		}
		else if (i == data->len_env)
		{
			ft_lstadd_back(new_env,
				ft_lstnew(ft_strdup(data->elements[arg_count])));
			data->len_env++;
		}
		else
			(ft_lstget(*new_env, i))->content =
				ft_strdup(data->elements[arg_count]);
		arg_count++;
	}
}
