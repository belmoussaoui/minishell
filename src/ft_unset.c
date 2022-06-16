/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:53:53 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/16 17:29:07 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_from_env(t_list **env, int i)
{
	t_list	*previous;
	t_list	*current;
	t_list	*next;

	previous = ft_lstget(*env, i - 1);
	current = ft_lstget(*env, i);
	next = ft_lstget(*env, i + 1);
	if (previous && next)
		previous->next = next;
	else if (previous && !next)
		previous->next = NULL;
	else if (!previous && next)
		current = next;
	else
		current = NULL;
	data->len_env--;
}

void	ft_unset(t_data *data, t_list **env)
{
	int		i;
	int		arg_count;
	char	**before;
	char	**elem_split;

	arg_count = 1;
	while (data->elements[arg_count])
	{
		i = 0;
		elem_split = ft_split(data->elements[arg_count], '=');
		while (i < data->len_env)
		{
			before = ft_split((ft_lstget(*env, i))->content, '=');
			if (!ft_strncmp(elem_split[0], before[0], ft_strlen(elem_split[0]))
				&& ft_strlen(elem_split[0]) == ft_strlen(before[0]))
				break ;
			i++;
		}
		if (i != data->len_env)
			unset_from_env(env, i);
		arg_count++;
	}
	debug_env(*env);		
}