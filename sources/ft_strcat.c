#include "../includes/minishell.h"

int	ft_strlen(char *str)
{
	int	i;
	while(str[i])
		i++;
	return (i);
}

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
