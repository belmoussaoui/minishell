/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:28:19 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/16 19:48:52 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_quotes(t_data *data, char** variable, int index)
{
	int		i;
	int		j;
	char 	*str;
	t_list	*lst;

	i = 0;
	lst = NULL;
	str = variable[index];
	while (str[i])
	{
		check_quote(data, str[i]);
		if (str[i] == '$' && data->s_quote == 0)
		{
			j = i;
			i++;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			char *value = malloc(sizeof(char) * ((i - j) + 1));
			ft_strlcpy(value, str + j, i - j + 1);
			i = 0;
			value = getenv(value + 1);
			while(value[i])
			{
				ft_lstadd_back(&lst, ft_lstnew(value + i));
				i++;
			}
		}
		if ((str[i] != '"' || data->s_quote) && (str[i] != '\'' || data->d_quote))
			ft_lstadd_back(&lst, ft_lstnew(str + i));
		i++;
	}
	variable[index] = malloc(sizeof(char) * ft_lstlen(lst));
	i = 0;
	while (lst)
	{
		variable[index][i] = ((char *) (lst->content))[0];
		lst = lst->next;
		i++;
	}
	variable[index][i] = '\0';
}

// Replace the variables with their values.
void	expander(t_data *data, t_list *commands)
{
	int		i;
	char	**elem;
	t_list	*start;

	start = commands;
	while (commands)
	{
		i = 0;
		while (((t_cmd *)(commands->content))->elements[i])
		{
			elem = ((t_cmd *)(commands->content))->elements;
			clear_quotes(data, elem, i);
			i++;
		}
		commands = commands->next;
	}
	commands = start;
}
