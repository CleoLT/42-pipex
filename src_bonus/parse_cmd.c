/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:13:36 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/16 14:07:57 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex_bonus.h"

static char	**get_env(char **envp)
{
	int		i;
	char	*env;
	char	**env_array;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env = envp[i] + 5;
			env_array = ft_split(env, ':');
			return (env_array);
		}
		i++;
	}
	return (NULL);
}

char	*parse_cmd(char *cmd, char **envp)
{
	int		i;
	char	**all_env;
	char	*path;
	char	*cmd_path;

	cmd_path = ft_strjoin("/", cmd);
	all_env = get_env(envp);
	if (!all_env)
		return (NULL);
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
	return (NULL);
}

char	*get_path(char *command, char **envp)
{
	char	*path;
	char	**cmd;


	if (command[0] == '\0')
		exit(-1);
	cmd = ft_split(command, ' ');
	path = parse_cmd(cmd[0], envp);
	if (!path && access(cmd[0], F_OK) == 0)
		path = ft_strdup(cmd[0]);
	if (!path)
		print_error("command not found: ", cmd[0], 127);
	else if (access(path, X_OK) != 0)
		print_error("permission denied: ", path, 126);
	free_array(cmd);
	return (path);
}

