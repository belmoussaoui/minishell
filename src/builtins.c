/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:24:04 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/15 19:45:51 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	*direction;

	(void) args;
	direction = NULL;
	if (!(direction = getcwd(direction, 0)))
		printf("Error pwd\n");
	printf("%s test\n", direction);
	free(direction);
	return (0);
}

void	ft_export(t_data *data, t_list **new_env)
{
	int 	i;
	int 	arg_count;
	char	**value;
	char	**elem_split;

	arg_count = 1;
	while (data->elements[arg_count])
	{
		i = 0;
		elem_split = ft_split(data->elements[arg_count], '=');
		while (i < data->len_env)
		{
			value = ft_split((ft_lstget(*new_env, i))->content, '=');
			if (!ft_strncmp(elem_split[0], value[0], ft_strlen(elem_split[0])))
				break;
			i++;
		}
		if (i == data->len_env)
			ft_lstadd_back(new_env, ft_lstnew(data->elements[arg_count]));
		arg_count++;
	}
}
// debug_env(*new_env);

void	ft_unset(t_data *data, char *envp[])
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(data->elements[1], envp[i], ft_strlen(data->elements[1])) == 0)
			printf("ft_unset\n");
		i++;
	}
}
