#include "pipex.h"


char	*ft_path(char *cmd, char **env)
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

char	*ft_pwd_p(char *cmd, char **env)
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
	exit(0);
}

void	get_cmd(char *av, char **env)
{
	char	**cmd;
	char	**cmd2;
	char	*path;
	int		i;

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
	path = ft_path(cmd[0], env);
	if (path == NULL)
		path = ft_pwd_p(cmd[0], env);
	if (execve(path, cmd, env) == -1)
	{
		perror("common error");
		exit(ERR_FILE_NOT_FOUND);
	}
}

void	ft_parent_process(char **av, char **env, int *fd)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("Output file error");
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(fd_out, 1);
	close(fd[1]);
	get_cmd(av[3], env);
}

void	child_process(char **av, int *fd, char **env)
{
	if (access(av[1], F_OK) == -1)
	{
		perror("input File does not exist");
		exit(ERR_FILE_NOT_FOUND);
	}
	if (access(av[1], R_OK) == -1)
	{
		perror("Permission denied\n");
		exit(ERR_PERMISSION_DENIED);
	}
	if (access(av[4], W_OK) == -1)
	{

		dup2(fd[1], 1);
		dup2(open(av[1], O_RDONLY), 0);
		close(fd[0]);
    	get_cmd(av[2], env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	fd[2];

	if (ac != 5)
		return (0);
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
		{
			close(fd[0]);
			close(fd[1]);
			while (wait(NULL) > 0)
				;
		}
	}
}
	
