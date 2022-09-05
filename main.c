/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:29:59 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/05 13:30:05 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize1(t_data *data, int argc, char **env)
{
	data->ac = argc;
	data->first_export = NULL;
	data->general.old_error = 0;
	if (env[0])
		data->env = env;
	else
		ft_create_my_env(data);
	ft_env(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	ft_initialize1(&data, argc, env);
	if (!ft_sub_main(&data))
		return (0);
}
