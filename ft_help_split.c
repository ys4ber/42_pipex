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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i])
	{
		i++;
	}
	return (i);
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
	int		str_len;
	int		i;

	str_len = ft_strlen(s);
	;
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
