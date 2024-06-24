/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:58:54 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/24 21:59:53 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	fill_buffer(int fd, char **buffer)
{
	int	chars_read;

	*buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (-1);
	chars_read = read(fd, *buffer, BUFFER_SIZE);
	if (chars_read == -1)
	{
		free(*buffer);
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

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stash;
	int			len;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	while ((fill_buffer(fd, &next_line)) > 0)
	{
		stash = ft_strjoin(stash, next_line);
		free(next_line);
		len = has_nl(stash);
		if (len >= 0)
		{
			line = ft_substr(stash, 0, len);
			temp = stash;
			stash = ft_substr(stash, len + 1, strlen(stash) - len - 1);
			free(temp);
			return (line);
		}
	}
	if (strlen(stash) > 0)
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
		return (line);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line read: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
