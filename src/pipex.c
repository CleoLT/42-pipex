/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/02/07 13:12:46 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

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
	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
		path = parse_cmd(cmd[0], envp);
	if (!path)
		print_error("command not found: ", cmd[0], 127);
	else if (access(path, X_OK) != 0)
		print_error("permission denied: ", path, 126);
	free_array(cmd);
	return (path);
}

static void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int		fd;
	char	*path;

	close(pipe_fd[READ_END]);
	if (access(argv[1], F_OK) != 0)
		print_error("no such file or directory: ", argv[1], 1);
	if (access(argv[1], R_OK) != 0)
		print_error("permission denied: ", argv[1], 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(-1);
	path = get_path(argv[2], envp);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		exit(-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit (-1);
	exec_cmd(path, argv[2], envp);
	free(path);
}

static void	parent_process(char **argv, char **envp, int *pipe_fd)
{
	int		fd;
	char	*path;

	close(pipe_fd[WRITE_END]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(argv[4], W_OK) != 0)
		print_error("permission denied: ", argv[4], 1);
	if (fd == -1)
		exit(-1);
	path = get_path(argv[3], envp);
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		exit(-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit(-1);
	exec_cmd(path, argv[3], envp);
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		*status;
	pid_t	pid;

	status = NULL;
	if (argc != 5)
		return (1);
	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_process(argv, envp, pipe_fd);
	if (ft_strncmp(argv[1], argv[4], ft_strlen(argv[1]) + 1) == 0)
		wait(status);
	if (pid > 0)
		parent_process(argv, envp, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}
