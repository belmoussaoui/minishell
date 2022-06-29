/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:31:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/29 18:03:48 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	count_split(t_data *data, char const *s, char c)
{
	int	count;
	int	i;
	int	trigger;

	count = 0;
	trigger = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && trigger)
		{
			count++;
			trigger = 0;
		}
		if (!check_quote(data, s[i]) && s[i] == c && !trigger)
			trigger = 1;
		i++;
	}
	clear_quote(data);
	return (count);
}

static	int	count_char(t_data *data, char const *s, char c)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i] && (s[i] != c || check == 1))
	{
		check = check_quote(data, s[i]);
		i++;
	}
	clear_quote(data);
	return (i);
}

void	*free_split(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	exit (EXIT_FAILURE);
}

char	**ft_split_quote(t_data *data, char const *s, char c)
{
	int		i;
	char	**res;
	int		current;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_split(data, s, c) + 1));
	if (!res)
		exit (EXIT_FAILURE);
	i = 0;
	current = 0;
	while (current < count_split(data, s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		res[current] = malloc(sizeof(char) * (count_char(data, s + i, c) + 1));
		if (res[current] == NULL)
			return (free_split(res));
		ft_strlcpy(res[current], s + i, count_char(data, s + i, c) + 1);
		i += count_char(data, s + i, c);
		current++;
	}
	res[current] = NULL;
	return (res);
}
