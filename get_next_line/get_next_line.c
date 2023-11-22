/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:26:47 by elakhfif          #+#    #+#             */
/*   Updated: 2023/11/22 04:14:22 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char	*get_next_line(int fd)
{
	char	*buffer;
	int		rd;
	int		i;
	char	c;

	i = 0;
	rd = 0;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((rd = read(fd, &c, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break;
	}
	buffer[i] = '\0';
	if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
		return (free(buffer), NULL);
	return (buffer);
}

#include <stdio.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
