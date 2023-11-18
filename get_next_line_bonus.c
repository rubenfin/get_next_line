/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:50:40 by rfinneru      #+#    #+#                 */
/*   Updated: 2023/11/18 17:28:08 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*trim_line_right(char *line, char **new_line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (ft_free(&line, NULL, 1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!str)
		return (ft_free(&line, new_line, 2));
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	ft_free(&line, NULL, 1);
	return (str);
}

char	*trim_line_left(char *line)
{
	size_t	i;
	char	*str;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	if (i == 0 && line[i] == '\0')
		return (NULL);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strncpy(str, line, i);
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*temp;
	size_t	i;

	if (!s)
		return (NULL);
	temp = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*read_buffer(int fd, char *line)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read == BUFFER_SIZE && !ft_strchr(line, '\n'))
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (ft_free(&line, NULL, 1));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(&line, &buffer, 2));
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line)
			return (ft_free(&buffer, NULL, 1));
		ft_free(&buffer, NULL, 1);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*new_line;

	if (BUFFER_SIZE == 0 || fd < 0 || fd > 1024)
		return (NULL);
	line[fd] = read_buffer(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	new_line = trim_line_left(line[fd]);
	line[fd] = trim_line_right(line[fd], &new_line);
	if (!new_line)
		ft_free(&line[fd], NULL, 1);
	return (new_line);
}

// int	main(void)
// {
// 	int		fd1;
// 	char	*out;

// 	// fd1 = 42;
// 	// fd1 = 0;
// 	fd1 = open("get_next_line.c", O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		printf("error opening file descriptor\n");
// 	}
// 	out = get_next_line(fd1);
// 	while (out)
// 	{
// 		printf("%s", out);
// 		free(out);
// 		out = get_next_line(fd1);
// 	}
// 	free(out);
// }
