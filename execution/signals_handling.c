/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:44:37 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/26 15:19:43 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	update_q_mark_variable(int new_value)
{
	g_vars.g_exit_stat = new_value;
	// add_to_local_env(ft_strdup("?"), ft_itoa(new_value));
}

void	sig_handler(int num)
{
	if (num == SIGINT && g_vars.g_where_ami)
	{
		g_vars.g_ctrl = 1;
		write(1, "\n", 1);
		rl_on_new_line(); 
    	rl_replace_line("", 0);
    	rl_redisplay();
	}
	if (num == SIGQUIT && g_vars.g_where_ami)
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			perror("signal(): error");
}
