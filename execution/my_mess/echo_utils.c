/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:02:01 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/15 14:04:19 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_cmd(char **argv, int argc, int i)
{
	char	*args;

	args = NULL;
	while (i < argc)
	{
		args = ft_strjoin(args, argv[i++]);
		args = ft_strjoin(args, " ");
	}
	return (args);
}

int	check_valid(char *cmd)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = cmd;
	while (tmp[i])
	{
		if (tmp[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
