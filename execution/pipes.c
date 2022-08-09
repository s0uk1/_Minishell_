/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:12:33 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/09 14:49:20 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	init_pipes(t_data *data)
{
    int	i;

    i = 0;
    data->pipes = malloc(sizeof(int) * data->nb_cmd);
    while (i < data->nb_cmd)
    {
        pipe(data->pipes + i);
        i++;
    }
}