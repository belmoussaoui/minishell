/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:31:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/22 13:37:47 by lrondia          ###   ########.fr       */
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

static	void	*free_strings(char **strings, int current)
{
	int	i;

	i = 0;
	while (i < current)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (NULL);
}

char	**ft_split_quote(t_data *data, char const *s, char c)
{
	int		i;
	char	**res;
	int		current;

	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char *) * (count_split(data, s, c) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	current = 0;
	while (current < count_split(data, s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		res[current] = malloc(sizeof(char) * (count_char(data, s + i, c) + 1));
		if (res[current] == NULL)
			return (free_strings(res, current));
		ft_strlcpy(res[current], s + i, count_char(data, s + i, c) + 1);
		i += count_char(data, s + i, c);
		current++;
	}
	res[current] = NULL;
	return (res);
}
