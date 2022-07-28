#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_envlst
{
	char *val_name;
	char *val;
	struct s_envlst *next;
}	t_envlst;

void	lst_add(t_envlst **lst, t_envlst *new);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
