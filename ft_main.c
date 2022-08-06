/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:37:19 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/29 14:41:56 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_initialize2(t_data *data)
{
	data->lst_cmd = NULL;
	data->lst_lexer = NULL;
	data->error = 0;
	data->her_doc = 0;
	data->general.index = 0;
	// rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	ft_free_norme(t_data *data)
{
	if (data->her_doc)
		free_split(data->eof);
	// if (data->paths)
	// 	free_split(data->paths);
	ft_free_lexer(data->lst_lexer);
	ft_free_cmd(data->lst_cmd);
}


// util function to add somewhere later 

char *ft_strcat(char *dest, char *src)
{
	int len;
	int	i;

	i = 0;
	len = ft_strlen(src);
	while(src[i])
	{
		dest[i + len] = src[i];
		i++;
	}
	dest[i + len] = '\0';
	return (dest);
}

void	ft_start(t_data *data)
{
	ft_expanding(data);
	ft_parsing(data);
	ft_print_cmd(data->lst_cmd);
	ft_builtins(data, data->lst_cmd);
	ft_free_norme(data);
}

int	ft_sub_main(t_data *data)
{
	while (42)
	{
		g_where_ami = 1;
		ft_initialize2(data);
		data->cmd = readline("minishell-1.0> ");
		if (!data->cmd)
			break ;
		if (data->cmd && data->cmd[0] != '\0')
		{
			ft_lexer(data);
			data->error = ft_syntax_analyzer(data);
			if (data->error)
			{
				ft_free_lexer(data->lst_lexer);
				data->general.old_error = data->error;
				continue ;
			}
			ft_start(data);
		}
		data->general.old_error = data->error;
	}
	// rl_clear_history();
	ft_free_env(data, data->lst_env);
	return (0);
}
