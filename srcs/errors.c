/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:12:12 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/10 02:31:52 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_error(char *str,char *aux)
{
	ft_putstr_fd(str,STDERR_FILENO);
	ft_putstr_fd(aux,STDERR_FILENO);
}