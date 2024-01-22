/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpipex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:18:11 by ysaber            #+#    #+#             */
/*   Updated: 2024/01/22 16:18:12 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		(perror("Error: Null command"), exit(126));
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
		(perror(""), exit(127));
}
