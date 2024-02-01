/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/01 17:14:09 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

void	process(char *cmd, char **envp)
{
	char	*path;

/*	path = get_env(envp);
	int i = 0;
	while (path[i])
	{
		printf("process : %s\n", path[i]);
		i++;
	}
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);*/
	path = get_path(cmd, envp);
	printf("process: %s\n", path);
	free(path);
//	char **cmd = ft_split(argv[1], ' ');
/*	if (access(cmd[0], F_OK) == 0)
		if (execve(cmd[0], cmd, envp) == -1)
			exit(90);
	else if (execve("/bin/ls", cmd, envp) == -1)
		exit(89);
	else
		perror(cmd[0]);
*/
}


int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5)
		return (3);	
//	print_env(envp);
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
