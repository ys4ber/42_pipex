#include "pipex.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

 int ft_strlen(const char *str)
{
    int i = 0;
    if (!str)
    {
        return 0;
    }
    while (str[i])
    {
        i++;
    }
    return i;
}


char	*ft_strdup(const char *src)
{
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (new_str == NULL)
	{
		return (NULL);
	}
	ft_strcpy(new_str, src);
	return (new_str);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*sub;
	int	str_len = ft_strlen(s);;
	int	i;
	
	
	if (start >= str_len)
		return (NULL);
	if (len > str_len - start)
		len = str_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[len] = '\0';
	return (sub);
}
void ft_putstr_fd(char *s, int fd)
{
    int i = 0;
    while(s[i])
        i++;
    write(fd, s, i);
}

char	*ft_strnstr(const char *str, const char *to_find, int len)
{
	int	i;
	int	j;

	if (to_find[0] == '\0')
		return ((char *)str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < len && str[i + j])
		{
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}



char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}