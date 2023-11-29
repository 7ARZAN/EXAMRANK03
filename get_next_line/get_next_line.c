/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:27:23 by elakhfif          #+#    #+#             */
/*   Updated: 2023/11/29 06:43:30 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif


int	find_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			str[j++] = s1[i++];

	i = 0;
	if (s2)
		while (s2 && s2[i])
			str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (*s)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}


char	*ft_read(int fd, char *buff, char *rest)
{
	char	*tmp;
	int	i;

	i = 1;
	while (i > 0 && find_new_line(rest) == -1)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i > 0)
		{
			buff[i] = '\0';
			tmp = ft_strjoin(rest, buff);
			free(rest);
			rest = tmp;
		}
	}
	free (buff);
	buff = NULL;
	if (i == -1)
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

char	*ft_line(char *rest)
{
	char	*line;
	int	i;
	int	indx;

	i = 0;
	if (ft_strlen(rest) <= 0)
		return (NULL);
	indx = find_new_line(rest);
	if (indx == -1)
	{
		line = ft_strdup(rest);
		return (line);
	}
	line = malloc(sizeof(char) * (indx + 2));
	if (!line)
		return (NULL);
	while (rest[i] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_rest(char *rest)
{
	int	len;
	int	i;
	char	*tmp;

	if (!rest)
		return (NULL);
	len = ft_strlen(rest);
	i = find_new_line(rest);
	if (i != -1)
	{
		tmp = ft_strdup(rest + i + 1);
		free (rest);
		rest = tmp;
		return (rest);
	}
	free(rest);
	return (NULL);
}


char	*get_next_line(int fd)
{
	static char	*rest;
	char	*line;
	char	*buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return(NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rest = ft_read(fd, buff, rest);
	line = ft_line(rest);
	rest = ft_rest(rest);
	return (line);
}

int	main()
{
	int	fd;

	fd = open("get_next_line.c", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}

