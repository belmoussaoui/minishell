/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:28:19 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/18 13:27:34 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	expands_element(t_data *data, char** variable)
{
	int		i;
	int		j;
	char 	*str;
	t_list	*lst;

	i = 0;
	lst = NULL;
	str = *variable;
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
			j = 0;
			value = getenv(value + 1);
			while(value[j])
			{
				ft_lstadd_back(&lst, ft_lstnew(value + j));
				j++;
			}
			i--;
		}
		else if ((str[i] != '"' || data->s_quote) && (str[i] != '\'' || data->d_quote))
			ft_lstadd_back(&lst, ft_lstnew(str + i));
		i++;
	}
	*variable = malloc(sizeof(char) * ft_lstlen(lst));
	i = 0;
	while (lst)
	{
		(*variable)[i] = ((char *) (lst->content))[0];
		lst = lst->next;
		i++;
	}
	(*variable)[i] = '\0';
	clear_quote(data);
}

// Replace the variables with their values.
void	expander(t_data *data, t_list *commands)
{
	int		i;
	t_cmd	*content;

	while (commands)
	{
		content = (t_cmd *)(commands->content);
		i = 0;
		while (content->elements[i])
		{
			expands_element(data, content->elements + i);
			i++;
		}
		commands = commands->next;
	}
}



// void	clear_quotes(t_data *data, char** variable, int index)
// {
// 	int		i;
// 	int		j;
// 	char 	*str;
// 	t_list	*lst;

// 	i = 0;
// 	lst = NULL;
// 	str = variable[index];
// 	while (str[i])
// 	{
// 		check_quote(data, str[i]);
// 		if (str[i] == '$' && data->s_quote == 0)
// 		{
// 			j = i;
// 			i++;
// 			while (ft_isalnum(str[i]) || str[i] == '_')
// 				i++;
// 			char *value = malloc(sizeof(char) * ((i - j) + 1));
// 			ft_strlcpy(value, str + j, i - j + 1);
// 			j = 0;
// 			value = getenv(value + 1);
// 			while(value[j])
// 			{
// 				ft_lstadd_back(&lst, ft_lstnew(value + j));
// 				j++;
// 			}
// 			i--;
// 		}
// 		else if ((str[i] != '"' || data->s_quote) && (str[i] != '\'' || data->d_quote))
// 			ft_lstadd_back(&lst, ft_lstnew(str + i));
// 		i++;
// 	}
// 	variable[index] = malloc(sizeof(char) * ft_lstlen(lst));
// 	i = 0;
// 	while (lst)
// 	{
// 		variable[index][i] = ((char *) (lst->content))[0];
// 		lst = lst->next;
// 		i++;
// 	}
// 	variable[index][i] = '\0';
// 	clear_quote(data);
// }

// // Replace the variables with their values.
// void	expander(t_data *data, t_list *commands)
// {
// 	int		i;
// 	t_list	*start;
// 	t_cmd	*content;

// 	start = commands;
// 	while (commands)
// 	{
// 		content = (t_cmd *)(commands->content);
// 		i = 0;
// 		while (content->elements[i])
// 		{
// 			clear_quotes(data, content->elements, i);
// 			i++;
// 		}
// 		commands = commands->next;
// 	}
// 	commands = start;
// }
