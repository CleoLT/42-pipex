/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:13:36 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/01 17:14:28 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

static char	**get_env(char **envp)
{
	int		i;
	char	*env;
	char	**env_array;

	i = 0;
	while (envp[i++])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env = envp[i] + 5;
			env_array = ft_split(env, ':');
			return (env_array);
		}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**all_env;
	char	*path;
	char	*cmd_path;

	cmd_path = ft_strjoin("/", cmd);
	i = 0;
	all_env = get_env(envp);
	while (all_env[i])
	{
		path = ft_strjoin(all_env[i], cmd_path);
		if (access(path, F_OK) == 0)
		{
			printf("%s\n", path);
			break;
		}
		free(path);
		i++;
	}
	free(cmd_path);
	i = 0;
	while (all_env[i])
	{
		free(all_env[i]);
		i++;
	}
	free(all_env);
	return (path);
}


