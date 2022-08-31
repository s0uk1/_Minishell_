# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <errno.h>
#include <string.h>
#include "minishell.h"

// char	*ft_substr(char *s, int start, size_t len)
// {
// 	char			*ptr;
// 	unsigned int	i;
// 	int				end;

// 	i = 0;
// 	end = len + start;
// 	if (!s)
// 		return (NULL);
// 	ptr = (char *)malloc((len + 1) * sizeof(char));
// 	if (!ptr)
// 		exit (1);
// 	if (start <= strlen(s))
// 	{
// 		while (start < end && s[start] != '\0')
// 		{
// 			ptr[i] = s[start];
// 			i++;
// 			start++;
// 		}
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }
// int main()
// {
//     char pwd[]= "alo ";
//     printf("%s", ft_substr(pwd, 0, strlen(pwd) - 1));
// }
int main ()
{
	int fd[2];
	if (pipe(fd) == -1)
		printf("error hehe\n");
	
	int pid1 = fork();
	if (pid1 < 0)
		return (42);

	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	

	int pid2 = fork();
	if (pid2 < 0)
		return (42);
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "round-trip", NULL);
 
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL,  0);
	waitpid(pid2, NULL, 0);
}