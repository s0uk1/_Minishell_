#include "../includes/minishell.h"

int	ft_strchr(const char *s, char c)
{
	size_t	i;
	size_t size;

	i = 0;
	size = ft_strlen(s);
	while (i < size)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (0);
	return (0);
}
