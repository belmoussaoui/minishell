/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:36:19 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/02 14:55:24 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

static size_t	compteur(char const *s, char c)
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
		if (s[i] == c && !trigger)
			trigger = 1;
		i++;
	}
	return (count);
}

static	int	len_word(char const *word, char c)
{
	int	i;

	i = 0;
	while (word[i] && word[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**word;
	size_t	iword;
	int		i;

	if (!s)
		return (NULL);
	iword = 0;
	i = 0;
	word = malloc(sizeof(char *) * (compteur(s, c) + 1));
	if (!word)
		return (0);
	word[compteur(s, c)] = NULL;
	while (iword < compteur(s, c))
	{
		while (s[i] == c)
			i++;
		word[iword] = malloc(sizeof(char) * (len_word(s + i, c) + 1));
		if (!word[iword])
			return (free_strings(word, iword));
		ft_strlcpy(word[iword], s + i, len_word(s + i, c) + 1);
		i = i + len_word(s + i, c);
		iword++;
	}
	return (word);
}
