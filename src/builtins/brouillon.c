/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:02:25 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/21 16:56:02 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (-1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_strncpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst && src)
	{
		while (src[i] && i < len)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}

void	ft_strinsert(char **astr, char *str, size_t i, size_t n)
{
	char	*dst;

	if (!astr || !*astr || !str)
		return ;
	dst = malloc((ft_strlen(*astr) + ft_strlen(str) + 1) * sizeof(char));
	if (dst)
	{
		ft_strncpy(dst, *astr, i);
		ft_strncpy(dst + i, str, n);
		ft_strncpy(dst + i + (ft_strlen(str), n), *astr + i, ft_strlen(*astr));
	}
	free(*astr);
	*astr = dst;
}

uint64_t	hash(char *key)
{
	uint64_t	sum;

	sum = 0;
	while (key && *key)
	{
		sum += *key;
		key++;
	}
	return (sum);
}

t_list	*table_find(t_list *table[TABLE_SIZE], char *key)
{
	t_list	*lst;

	lst = table[hash(key) % TABLE_SIZE];
	while (lst)
	{
		if (!ft_strcmp(*((t_cmd *)lst->content)->elements, key))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static char *get_path(t_data *data)
{
	char	*path;
	char	*user = NULL;
	t_list	*commands;

	if (data->elements[1])
	{
		path = getcwd(NULL, 0);
		ft_strinsert(&path, "/", ft_strlen(path), 1);
		ft_strinsert(&path, data->elements[1], ft_strlen(path), ft_strlen(data->elements[1]));
	}
	else
	{
		commands = table_find(&data->commands, "USER");
		path = ft_strdup("/Users/");
		user = (char *)((t_cmd *)commands->content)->elements;
		ft_strinsert(&path, user, ft_strlen(path), ft_strlen(user));
	}
	return (path);
}

static char	*get_path(char **cmds, t_shell *shell)
{
	char	*path;
	char	*user;
	t_list	*node;

	if (cmds[1])
	{
		path = getcwd(NULL, 0);
		str_n_insert(&path, "/", str_len(path), 1);
		str_n_insert(&path, cmds[1], str_len(path), str_len(cmds[1]));
	}
	else
	{
		node = table_find(shell->table, "USER");
		if (!node)
		{
			put_str_fd(NO_USER, STDERR_FILENO);
			return (NULL);
		}
		path = str_dup("/Users/");
		user = (char *)((t_var *)node->content)->data;
		str_n_insert(&path, user, str_len(path), str_len(user));
	}
	return (path);
}

// void    ft_cd(t_data *data)
// {
// 	char	*path;
// 	char	*user = NULL;
// 	t_list	*commands;
//     (void) data;
//     const char *home = getenv("HOME");
//     //const char *racine = getenv("/");

//     printf("%s\n", data->elements[0]);
//     if (ft_strcmp(data->elements[0], "cd") == 0)
//         chdir(home);
//     if (!ft_strcmp(data->elements[1], "~"))
//         chdir(home);
// 	else if (!ft_strcmp(data->elements[1], ".."))
// 		chdir("..");
// 	while (!ft_strcmp(data->elements[1], "/"))
// 	{
// 		chdir("..");
// 		break ;
// 	}
// }

bool	ft_cd(t_data *data)
{
	char	*path;

	if (!data->elements || ft_strcmp("cd", *data->elements))
		return (true);
	path = get_path(data);
	printf("path = %s\n", path);
	printf("cmds = %s\n", *data->elements);

	if (!path)
		return (true);
	if (chdir(path) < 0)
	{
		perror(path);
		free(path);
		return (true);
	}
	free (path);
	return (false);
}

