#include "../minishell.h"

char	*ft_var_isnt(t_data *data, char *lexer, char *n_v)
{
	char	*temp;

	temp = ft_delete_var(data, lexer);
	n_v = ft_strjoin(n_v, temp);
	free(temp);
	return (n_v);
}
