/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:16:03 by xgossing          #+#    #+#             */
/*   Updated: 2024/08/29 18:16:04 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * this function will be compiled using CC, NOT GCC
 * the next line should include the '\n' at the end
 * except when the file has reached its end and no '\n' remains
 * it should return the line that was read, or NULL if
 * either the file is empty/has reached its end, or on error
 */
#include "include/get_next_line_bonus_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!remainder[fd])
	{
		remainder[fd] = gnl_calloc(1, 1);
		remainder[fd][0] = 0;
	}
	read_line(fd, &remainder[fd]);
	if (remainder[fd] == NULL)
		return (NULL);
	line = get_clean_line(remainder[fd]);
	remainder[fd] = trim_rest(remainder[fd]);
	return (line);
}

// reads the next line
// returns that line with a newline (or NULL-terminator)
// and possibly some garbage afterwards
void	read_line(int fd, char **remainder)
{
	int		bytes_read;
	char	*buffer;

	if (*remainder != NULL && gnl_strchr(*remainder, '\n'))
		return ;
	buffer = gnl_calloc(sizeof(char) * (BUFFER_SIZE + 1), 1);
	if (!buffer)
		return ;
	bytes_read = 69;
	while (bytes_read != 0 && !gnl_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(*remainder);
			*remainder = NULL;
			return ;
		}
		buffer[bytes_read] = '\0';
		*remainder = gnl_strjoin(*remainder, buffer);
	}
	free(buffer);
}

// returns line up until the first newline
char	*get_clean_line(char *line)
{
	int		i;
	int		clean_i;
	char	*clean_line;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	clean_line = gnl_calloc(sizeof(char) * (i + 1), 1);
	if (!clean_line)
		return (free_and_null(line));
	clean_i = 0;
	while (clean_i < i)
	{
		clean_line[clean_i] = line[clean_i];
		clean_i++;
	}
	clean_line[clean_i] = '\0';
	return (clean_line);
}

// trims off the previous line
char	*trim_rest(char *line)
{
	int		i;
	int		trim_i;
	char	*remainder;

	i = 0;
	if (!line[i])
		return (free_and_null(line));
	i = gnl_strlen_char(line, '\n');
	remainder = gnl_calloc((gnl_strlen(&line[i]) + 1), 1);
	if (!remainder)
		return (free_and_null(line));
	trim_i = 0;
	while (line[i])
		remainder[trim_i++] = line[i++];
	remainder[trim_i] = '\0';
	free(line);
	if (!remainder[0])
		return (free_and_null(remainder));
	return (remainder);
}

char	*free_and_null(char *str)
{
	free(str);
	return (NULL);
}
