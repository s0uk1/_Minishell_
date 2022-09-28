/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:44:37 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/28 10:53:49 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int num)
{
	if (num == SIGINT && g_vars.g_where_ami)
	{
		g_vars.g_exit_stat = 1;
		write(1, "\n", 1);
    	// rl_replace_line("", 0);
		rl_on_new_line(); 
    	rl_redisplay();
	}
	if (num == SIGQUIT && g_vars.g_where_ami)
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			perror("signal(): error");
}
