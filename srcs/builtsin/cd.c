/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:41:13 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/05 07:45:14 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void cd (t_shell *shell)
{
if(shell->input[2] == '\0')
		chdir(shell->home);
else if (chdir(shell->input + 3) == -1)
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
}