#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_envlst
{
	char *val_name;
	char *val;
	struct s_envlst *next;
}	t_envlst;

typedef struct	s_cmdex
{
	char	cwd[256];
	char	**cmd;
	char	**env;
}	t_cmdex;

typedef	struct	s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct	s_data
{
	t_envlst	*lst_env;
	t_cmd		*lst_cmd;
} t_data;
int		ft_strcat(char *dest, char *src);
int		ft_strchr(const char *s, char c);
void	lst_add(t_envlst **lst, t_envlst *new);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
