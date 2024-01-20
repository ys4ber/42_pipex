#include "pipex.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

static void	test(char **ret, int i, int j)
{
	while (j < i)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

static int	fill_string(const char *s, char c, char **ret, int len)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			ret[i] = ft_substr(s - len, 0, len);
			if (!ret[i])
			{
				test(ret, i, 0);
				return (0);
			}
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char **ret;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!ret)
		return (NULL);
	if (fill_string(s, c, ret, 0) == 0)
		return (NULL);
	return (ret);
}