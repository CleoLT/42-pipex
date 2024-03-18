/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tron <ale-tron@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:38:04 by ale-tron          #+#    #+#             */
/*   Updated: 2024/03/18 11:46:51 by ale-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	print_error(char *str, char *cmd, int exit_code)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(cmd, 2);
	exit(exit_code);
}

void	ft_error(char *arg, int exit_code)
{
	perror(arg);
	exit(exit_code);
}
