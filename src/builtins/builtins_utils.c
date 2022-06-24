/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:24:04 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/24 16:58:14 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "unset", 6)
		|| !ft_strncmp(cmd_name, "export", 7)
		|| !ft_strncmp(cmd_name, "pwd", 4)
		|| !ft_strncmp(cmd_name, "cd", 3)
		|| !ft_strncmp(cmd_name, "echo", 5)
		|| !ft_strncmp(cmd_name, "env", 4));
}

void	run_builtin(t_data *data, char *cmd_name)
{
	if (!ft_strncmp(cmd_name, "unset", 6))
		ft_unset(data, &data->new_env);
	else if (!ft_strncmp(cmd_name, "export", 7))
		ft_export(data, &data->new_env);
	else if (!ft_strncmp(cmd_name, "env", 4))
		ft_env(data->new_env);
	else if (!ft_strncmp(cmd_name, "cd", 3))
		ft_cd(data);
	else if (!ft_strncmp(cmd_name, "echo", 5))
		ft_echo(data);
	else if (!ft_strncmp(cmd_name, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd_name, "exit", 5))
		ft_exit();
}

int	cmp_env(t_data *data, t_list **new_env, int arg_count)
{
	char	**elem_split;
	char	**value;
	int		i;

	i = 0;
	elem_split = ft_split(data->elements[arg_count], '=');
	if (!ft_strchr(data->elements[arg_count], '='))
		exit(1);
	while (i < data->len_env)
	{
		value = ft_split((ft_lstget(*new_env, i))->content, '=');
		if (!ft_strncmp(elem_split[0], value[0], ft_strlen(elem_split[0])))
			break ;
		free_split(value);
		i++;
	}
	return (i);
}

char	*get_env(t_list *env, char *name)
{
	char	*content;
	int		len_name;

	len_name = ft_strlen(name);
	while (env)
	{
		content = (char *) env->content;
		if (!ft_strncmp(name, content, len_name) && content[len_name] == '=')
			return (content + len_name + 1);
		env = env->next;
	}
	return (NULL);
}

int	is_parent_cmd(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "unset", 6)
		|| !ft_strncmp(cmd_name, "export", 7)
		|| !ft_strncmp(cmd_name, "cd", 3)
		|| !ft_strncmp(cmd_name, "exit", 5));
}
