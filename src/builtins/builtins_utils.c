/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:24:04 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/16 17:53:26 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "unset", 6)
		|| !ft_strncmp(cmd_name, "export", 7));
}

int	ft_pwd(void)
{
	char	*direction;

	direction = NULL;
	direction = getcwd(direction, 0);
	if (!direction)
		printf("Error pwd\n");
	printf("%s test\n", direction);
	free(direction);
	return (0);
}

int	cmp_env(t_data *data, t_list **new_env)
{
	char	**elem_split;
	int		arg_count;
	char	**value;
	int		i;

	i = 0;
	arg_count = 1;
	elem_split = ft_split(data->elements[arg_count], '=');
	while (i < data->len_env)
	{
<<<<<<< HEAD:src/builtins.c
		i = 0;
		elem_split = ft_split(data->elements[arg_count], '=');
		while (i < data->len_env)
		{
			value = ft_split((ft_lstget(*new_env, i))->content, '=');
			if (!ft_strncmp(elem_split[0], value[0], ft_strlen(elem_split[0])))
				break ;
			i++;
		}
		if (i == data->len_env)
			ft_lstadd_back(new_env, ft_lstnew(data->elements[arg_count]));
		else
			printf("je suis la\n");
		arg_count++;
	}
debug_env(*new_env);
=======
		value = ft_split((ft_lstget(*new_env, i))->content, '=');
		if (!ft_strncmp(elem_split[0], value[0], ft_strlen(elem_split[0])))
			break ;
		i++;
	}
	return (i);
>>>>>>> 6af2652194e046a14feca4866ac49e5761dd56a0:src/builtins/builtins_utils.c
}

void	ft_unset(t_data *data, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(data->elements[1], envp[i],
				ft_strlen(data->elements[1])) == 0)
			printf("ft_unset\n");
		i++;
	}
}

void	run_builtin(t_data *data, char *cmd_name, char *envp[])
{
	if (!ft_strncmp(cmd_name, "unset", 6))
		ft_unset(data, envp);
	else if (!ft_strncmp(cmd_name, "export", 7))
		ft_export(data, &data->new_env);
}
