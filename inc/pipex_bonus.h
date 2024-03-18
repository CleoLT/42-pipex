/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:54:55 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/18 11:46:51 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <fcntl.h>

# define WRITE_END 1
# define READ_END 0

char	*parse_cmd(char *cmd, char **envp);
char	*get_path(char *command, char **envp);
void	free_array(char **array);
void	print_error(char *str, char *cmd, int exit_code);

void	ft_error(char *arg, int exit_code);

#endif
