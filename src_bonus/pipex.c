/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/15 18:01:58 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex_bonus.h"

static void	exec_cmd(char *path, char *command, char **envp)
{
	char	**cmd;

	cmd = ft_split(command, ' ');
	if (execve(path, cmd, envp) == -1)
		exit(-1);
	free_array(cmd);
}

static char	*get_path(char *command, char **envp)
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
		print_error("permission denied: holaaa", path, 126);
	free_array(cmd);
	return (path);
}

static void	child_process(char *argvi, char **envp, int *pipe_fd)
{
	char	*path;

	close(pipe_fd[READ_END]);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		exit(1);

	path = get_path(argvi, envp);
	exec_cmd(path, argvi, envp);
	free(path);
}

static void make_pipe(char *argvi, char **envp, int i)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (i == 2)
	{
	
printf("hola");

	
	}	
	if (pipe(pipe_fd) == -1)
		exit (1);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
		child_process(argvi, envp, pipe_fd);
	if (pid > 0)
	{
		close(pipe_fd[WRITE_END]);
		if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
			exit(-1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	int		fd_in;
	int		fd_out;
	int		i;
	
	if (argc < 5)
		return (1);
	if (access(argv[1], F_OK) != 0)
		print_error("no such file or directory: ", argv[1], errno);
	if (access(argv[1], R_OK) != 0)
		print_error("permission denied: ", argv[1], errno);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		exit(1);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(argv[argc - 1], W_OK) != 0)
		print_error("permission denied: ", argv[argc - 1], 1);
	if (fd_out == -1)
		exit(1);
//	if (dup2(fd_in, STDIN_FILENO) == -1)
//		exit (1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	i = 2;
	while (i < argc - 2)
	{
		make_pipe(argv[i], envp, i);
		i++;
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	path = get_path(argv[i], envp);
	exec_cmd(path, argv[i], envp);
	free(path);
	return (0);
}
