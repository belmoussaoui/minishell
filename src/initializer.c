/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:05:53 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/13 18:54:26 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(int argc, char *argv[], t_list **new_env)
{
	(void) argc;

	if (ft_strncmp(argv[1], "export", 7) == 0)
	{
		ft_lstadd_back(new_env, ft_lstnew(argv[2]));
	}
}

void	ft_env(int argc, char *argv[], char *envp[])
{
	t_list			*new_env;
	t_environment	env;
	int				i;

	(void) argc;
	(void) argv;
	new_env = NULL;
	i = 0;
	
	while (envp[i] != 0)
	{
		ft_lstadd_back(&new_env, ft_lstnew(envp[i]));
		env.before = ft_split(new_env->content, '=')[0];
		env.after = ft_split(new_env->content, '=')[1];
		new_env = new_env->next;
		printf("Avant : %s\n", env.before);
		printf("Apres : %s\n", env.after);
		i++;
	}
	ft_export(argc, argv, &new_env);
	printf("%s\n", new_env->content);


}

// Intialize minishell data and setup the environment.
void	initializer(t_data *data, int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	(void) envp;
	data->commands = NULL;
	//printf("La valeur de %s est %s\n", argv[1], getenv(argv[1]));
	ft_env(argc, argv, envp);
}
