/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:50:42 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/11/10 16:47:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	return (NULL);
}

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!dest || !src)
		return (dest);
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*full_s;
	int		i;

	if (ft_strlen(s1) + ft_strlen(s2) == 0)
	{
		return (ft_free(&s1));
	}
	full_s = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1)
			* sizeof(char));
	if (!full_s)
		return (ft_free(&s1));
	i = 0;
	while (s1[i])
	{
		full_s[i] = s1[i];
		i++;
	}
	while (*s2)
		full_s[i++] = *(s2++);
	full_s[i] = '\0';
	ft_free(&s1);
	return (full_s);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen((char *)s)]);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
