/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/28 03:36:59 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	char *pwd;
	char *cdroute;
	char *cdin;
	int i;
	i=0;
 	pwd =  getcwd(NULL,0);
    printf("%s\n", pwd);
	cdroute = ft_strrchr(pwd,'/');
	cdin = ft_substr(pwd,0, ft_strlen(pwd) - ft_strlen(cdroute));
    printf("%s\n",cdin);
	chdir(cdin);
	pwd =  getcwd(NULL,0);
    printf("%s\n", pwd);
	
		
    return (0);
	
}
