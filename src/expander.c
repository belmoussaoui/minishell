/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:28:19 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/22 17:16:56 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expands_variable(t_data *data, t_list **new, char *element)
{
	int		len_var;
	char	*name_var;
	char	*val_var;
	int		i;

	len_var = 0;
	while (ft_isalnum(element[len_var]) || element[len_var] == '_')
		len_var++;
	name_var = malloc(sizeof(char) * (len_var + 1));
	if (!name_var)
		exit(EXIT_FAILURE);
	ft_strlcpy(name_var, element, len_var + 1);
	val_var = get_env(data->new_env, name_var);
	if (!val_var)
		val_var = "";
	free(name_var);
	i = 0;
	while (val_var[i])
	{
		ft_lstadd_back(new, ft_lstnew(val_var + i));
		i++;
	}
	return (len_var);
}

void	remplace_element(t_list *new, char **element)
{
	int		i;
	char	*copy;

	copy = *element;
	*element = malloc(sizeof(char) * ft_lstlen(new));
	if (!*element)
		exit(EXIT_FAILURE);
	i = 0;
	while (new)
	{
		(*element)[i] = ((char *)(new->content))[0];
		new = new->next;
		i++;
	}
	(*element)[i] = '\0';
	free(copy);
}

void	expands_element(t_data *data, char **element)
{
	int		i;
	char	*str;
	t_list	*new;

	i = 0;
	new = NULL;
	str = *element;
	while (str[i])
	{
		check_quote(data, str[i]);
		if (str[i] == '$' && data->s_quote == 0)
			i += expands_variable(data, &new, str + i + 1);
		if ((str[i] != '"' || data->s_quote)
			&& (str[i] != '\'' || data->d_quote))
			ft_lstadd_back(&new, ft_lstnew(str + i));
		i++;
	}
	remplace_element(new, element);
	ft_lstclear(&new, NULL);
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
