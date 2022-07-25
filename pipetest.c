#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main()
{
	int arr[] = {1 , 2, 3, 4, 5, 6, 7};
	int start;
	int end;
	int arr_size;
	arr_size = sizeof(arr) / sizeof(int);
	int sum = 0;
	int	i = 0;

	int fd[2];
	if (pipe(fd) == -1)
		return (69);
	int id = fork();
	if (id == -1)
		return (420);
	if (id == 0) //we're in the child process
	{
		start = 0;
		end = arr_size / 2;
	}
	else 
	{
		start = arr_size / 2;
		end = arr_size;
	}
	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("calclulated partial sum %d\n", sum);
	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else 
	{
		int child_sum;
		int total_sum;
		close(fd[1]);
		read(fd[0], &child_sum, sizeof(child_sum));
		close(fd[0]);
		total_sum = sum +child_sum;
		printf("total_sum is %d", total_sum);
		wait(NULL);
	}
}
