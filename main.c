/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:29:59 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/23 16:37:01 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_initialize1(t_data *data, int argc, char **env)
{
	data->ac = argc;
	data->first_export = NULL;
	data->general.old_error = 0;
	data->general.index = 0;
	if (env[0])
		data->env = env;
	else
	{
		printf("uwu where's your env anon\n");
		return (0);
	}
	ft_env(data);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (!ft_initialize1(&data, argc, env))
		exit(1);
	if (!ft_sub_main(&data))
		return (0);
}
