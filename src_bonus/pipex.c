/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/16 14:08:24 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex_bonus.h"



static void	exec_cmd(char *command, char **envp)
{
	char	**cmd;
	char	*path;

	path = get_path(command, envp);
	cmd = ft_split(command, ' ');
	if (execve(path, cmd, envp) == -1)
		exit(-1);
	free_array(cmd);
	free(path);
}

static void	child_process(char *arg, char **envp, int *pipe_fd)
{
	
	close(pipe_fd[READ_END]);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		exit(1);
	exec_cmd(arg, envp);
}

static void	open_infile(char **argv)
{
	int	fd_in;

	if (access(argv[1], F_OK) != 0)
		print_error("no such file or directory: ", argv[1], errno);
	if (access(argv[1], R_OK) != 0)
		print_error("permission denied: ", argv[1], errno);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		exit(1);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit (1);
}

static void make_pipe(char **argv, char **envp, int i)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		exit (1);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (i == 2)
			open_infile(argv);	
		child_process(argv[i], envp, pipe_fd);
	}
	if (pid > 0)
	{
		close(pipe_fd[WRITE_END]);
		if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
			exit(-1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_out;
	int		i;
	int	status;
	
	if (argc < 5)
		return (1);
	i = 2;
	while (i < argc - 2)
	{
		make_pipe(argv, envp, i);
		i++;
	}
	wait(&status);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(argv[argc - 1], W_OK) != 0)
		print_error("permission denied: ", argv[argc - 1], 1);
	if (fd_out == -1)
		exit(1);
	if (dup2(fd_out, STDOUT_FILENO) == -1) 
		exit(1);
	exec_cmd(argv[i], envp);
	return (0);
}
