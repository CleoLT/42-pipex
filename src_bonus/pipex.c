/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:20 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/21 12:23:42 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex_bonus.h"

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

static void	create_heredoc_file(char **argv)
{
	int		fd_heredoc;
	char	*line;

	fd_heredoc = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_heredoc == -1)
		ft_error("open function", errno);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!ft_strncmp(argv[2], line, ft_strlen(argv[2])))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_heredoc);
		free(line);
	}
	close(fd_heredoc);
	fd_heredoc = open(".heredoc", O_RDONLY);
	if (dup2(fd_heredoc, STDIN_FILENO) == -1)
		exit (1);
}

static void	make_pipe(char **argv, char **envp, int i)
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
		if (i == INFILE_MODE)
			open_infile(argv);
		else if (i == HEREDOC_MODE && !ft_strncmp(argv[1], "here_doc", 8))
			create_heredoc_file(argv);
		child_process(argv[i], envp, pipe_fd);
	}
	if (pid > 0)
	{
		close(pipe_fd[WRITE_END]);
		if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
			exit(-1);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_out;
	int	i;
	int	status;

	if (argc < 5)
		return (1);
	i = INFILE_MODE;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc < 6)
			return (1);
		i = HEREDOC_MODE;
	}
	while (i < argc - 2)
		make_pipe(argv, envp, i++);
	wait(&status);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(argv[argc - 1], W_OK) != 0)
		ft_error(argv[argc - 1], errno);
	if (fd_out == -1)
		exit(1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	exec_cmd(argv[i], envp);
	return (0);
}

/*
static void	heredoc_process(char **argv, int *pipe_fd)
{
	char	*line = NULL;

	close(pipe_fd[READ_END]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!ft_strncmp(argv[2], line, ft_strlen(argv[2])))
		{
			free(line);
			exit (0);	
			break;
		}
		ft_putstr_fd(line, pipe_fd[WRITE_END]);
		free(line);
	}
}
*/
