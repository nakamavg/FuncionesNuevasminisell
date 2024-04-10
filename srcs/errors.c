/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:12:12 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/10 19:43:00 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, char *aux)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(aux, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ft_error_cmd(char *str, char *aux)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(aux, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(1);
}

void	ft_error3(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(1);
}
