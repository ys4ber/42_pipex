#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERR_FILE_NOT_FOUND 127
# define ERR_PERMISSION_DENIED 1
# define ERR_PIPE_ERROR 125

char	**ft_split(const char *s, char c);
int		ft_strlen(const char *str);
char	*ft_strnstr(const char *str, const char *to_find, int len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_get_path(char *cmd, char **env);

int		main(int argc, char **argv, char **env);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);
void	ft_check_args(char **av);

#endif