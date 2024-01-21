#include "pipex.h"

#define errno 0


char	*ft_get_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*piece_path;
	char	*res;
	int		i;

	i = 0;
	if (env == NULL)
		exit(1);
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	all_paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		piece_path = ft_strjoin(all_paths[i], "/");
		res = ft_strjoin(piece_path, cmd);
		if (access(res, F_OK) == 0)
			return (res);
		else
			free(res);
		i++;
	}
	return (NULL);
}

char	*ft_pwd_p(char *cmd, char **env, char *av)
{
	char	*pwd_p;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (env == NULL)
		exit(1);
	while (env[i] && ft_strnstr(env[i], "PWD=", 4) == 0)
		i++;
	if (env[i] == NULL)
		exit(0);
	pwd_p = malloc(ft_strlen(env[i]) - 4);
	while (++j < ft_strlen(env[i]) - 4)
		pwd_p[j] = env[i][j + 4];
	pwd_p = ft_strjoin(pwd_p, "/");
	res = ft_strjoin(pwd_p, cmd);
	if (access(res, F_OK) == 0)
		return (res);
	else
		free(res);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": my pipex: command not found\n", 2);
	exit(127);
}

void	get_cmd(char *av, char **env)
{
	char	**cmd;
	char	**cmd2;
	char	*path;
	int		i;

	if (av == NULL)
		exit(126);
	i = 0;
	cmd2 = ft_split(av, ' ');
	cmd = ft_split(av, ' ');
	if (access(cmd[0], F_OK) == 0)
	{
		cmd = ft_split(av, ' ');
		while (cmd[i])
			i++;
		cmd = ft_split(cmd[i - 1], ' ');
		execve(cmd2[0], cmd, env);
	}
	path = ft_get_path(cmd[0], env);
	if (path == NULL)
		path = ft_pwd_p(cmd[0], env, av);
	if (execve(path, cmd, env) == -1)
		(perror("command error\n"), exit(127));
}

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

void close_fd(int *fd, int n)
{
	close(fd[0]);
	close(fd[1]);
	while (wait(&n) > 0)
		;
	if (WIFEXITED(n))
		exit(WEXITSTATUS(n));
	exit(127);
}

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	fd[2];
	int	n;

	if (ac != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		exit(1);
	}
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
