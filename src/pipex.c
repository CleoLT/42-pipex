/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/03 12:15:06 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

static void	process(char *command, char **envp, pid_t pid)
{
	char	*path;
	char	**cmd;

	if (command[0] == '\0')
		return ;
	cmd = ft_split(command, ' ');
//	printf("cmd : %s   //   %s \n", cmd[0], cmd[1]);
	path = get_path(cmd[0], envp);
	printf("process: %s\n\n", path);
	if (!path)
	{
		print_error("command not found: ", cmd[0]);
	//	free_array(cmd);
		if (pid > 0)
			exit(127);
	}
	else if (access(path, X_OK) != 0)
	{
		print_error("permission denied: ", path);
	//	if (pid > 0)
			exit(126);
	}
	else if (execve(path, cmd, envp) == -1)
	{
		print_error("error", "error");
//		free_array(cmd);
//		if (pid > 0)
//			exit(127);
	}
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5 || envp[0] == NULL)
		return (1);
	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		process(argv[2], envp, pid);
	if (pid > 0)
		process(argv[3], envp, pid);
	return (0);
}
