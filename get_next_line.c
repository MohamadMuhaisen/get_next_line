/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:58:54 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/25 16:58:22 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	fill_buffer(int fd, char **buffer)
{
	ssize_t	chars_read;

	*buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!*buffer)
		return (-1);
	chars_read = read(fd, *buffer, BUFFER_SIZE);
	if (chars_read <= 0 || fd < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (-1);
	}
	(*buffer)[chars_read] = '\0';
	return (chars_read);
}

int	has_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_line_from_stash(char **stash)
{
	int		len;
	char	*line;
	char	*temp;

	len = has_nl(*stash);
	if (len >= 0)
	{
		line = ft_substr(*stash, 0, len + 1);
		temp = *stash;
		*stash = ft_substr(*stash, len + 1, ft_strlen(*stash) - len - 1);
		free(temp);
		return (line);
	}
	if (ft_strlen(*stash) > 0)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	return (NULL);
}

void	read_and_append(int fd, char **stash)
{
	char	*next_line;
	char	*temp;

	while (fill_buffer(fd, &next_line) > 0)
	{
		temp = *stash;
		*stash = ft_strjoin(*stash, next_line);
		free(temp);
		free(next_line);
		if (has_nl(*stash) >= 0)
			break ;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash)
		stash = ft_strdup("");
	read_and_append(fd, &stash);
	line = get_line_from_stash(&stash);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
// 		return (1);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line read: %s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
