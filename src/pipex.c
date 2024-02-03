/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/03 16:11:04 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

static void	exec_cmd(char *command, char **envp)
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
	//	if (pid > 0)
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

static void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[READ_END]);
	fd = open(argv[1], O_RDONLY);
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	


	exec_cmd(argv[2], envp);
}

static void parent_process(char **argv, char **envp, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[WRITE_END]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);

	exec_cmd(argv[3], envp);
}
			
int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;
	
	printf("%d  /// %d   \n", pipe_fd[0], pipe_fd[1]);	
	if (argc != 5 || envp[0] == NULL)
		return (1);
	if (pipe(pipe_fd) == -1)
		return (1);
	printf("%d  /// %d   \n", pipe_fd[0], pipe_fd[1]);	
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_process(argv, envp, pipe_fd);
	if (pid > 0)
		parent_process(argv, envp, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}
