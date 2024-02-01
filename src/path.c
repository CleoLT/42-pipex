/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:13:36 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/01 18:39:03 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

static void	free_array(char **array)
{
	int	i;
	
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

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
	
	if (cmd[0] == '\0')
		return (NULL);
	cmd_path = ft_strjoin("/", cmd);
	all_env = get_env(envp);
	i = 0;
	while (all_env[i])
	{
		path = ft_strjoin(all_env[i], cmd_path);
		if (access(path, F_OK) == 0)
		{
			free(cmd_path);
			free_array(all_env);		
			return (path);
		}
		free(path);
		i++;
	}
	free(cmd_path);
	free_array(all_env);
//	perror(cmd);
	return (NULL);
}
