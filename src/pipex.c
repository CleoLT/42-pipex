/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/01 18:38:53 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

static void	process(char *command, char **envp)
{
	char	*path;
	char	**cmd;
	
	path = get_path(command, envp);
	printf("process: %s\n", path);
	cmd = ft_split(command, ' ');
	if (access(cmd[0], F_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			exit(90);
	}
	else if (execve(path, cmd, envp) == -1)
		perror(cmd[0]);
	else
		perror(cmd[0]);

	free(path);
}


int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5)
		return (3);	
	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
		process(argv[2], envp);
	if (pid > 0)
		process(argv[3], envp);
	return (0);
}
