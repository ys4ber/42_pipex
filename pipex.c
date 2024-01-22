#include "pipex.h"

void	ft_parent_process(char **av, char **env, int *fd)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("");
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(fd_out, 1);
	close(fd[1]);
	get_cmd(av[3], env);
}

void	child_process(char **av, int *fd, char **env)
{
	int	fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
	{
		ft_putstr_fd(av[1], 2);
		perror(" ");
		exit(1);
	}
	dup2(fd[1], 1);
	dup2(fd_in, 0);
	close(fd[0]);
	get_cmd(av[2], env);
}
void	close_fd(int *fd, int n)
{
	close(fd[0]);
	close(fd[1]);
	while (wait(&n) > 0)
		;
	if (WIFEXITED(n))
		exit(WEXITSTATUS(n));
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	int pid;
	int fd[2];
	int n;

	if (ac != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		exit(1);
	}
	n = 0;
	if (pipe(fd) == -1)
		(perror("Pipe error"), exit(ERR_PIPE_ERROR));
	pid = fork();
	if (pid == 0)
		child_process(av, fd, env);
	else
	{
		pid = fork();
		if (pid == 0)
			ft_parent_process(av, env, fd);
		else
			close_fd(fd, n);
	}
}