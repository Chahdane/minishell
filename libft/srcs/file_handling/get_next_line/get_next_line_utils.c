/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:05:33 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/06 21:16:40 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//gnl stands for get_next_line
static size_t	gnl_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	return (len);
}

static int	manage_buff(char **buff, size_t buff_len)
{
	char	*tmp;
	size_t	i;

	if (!(*buff)[buff_len])
	{
		free(*buff);
		*buff = NULL;
		return (1);
	}
	i = 0;
	while ((*buff)[buff_len + i])
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while ((*buff)[buff_len + i])
	{
		tmp[i] = (*buff)[buff_len + i];
		i++;
	}
	tmp[i] = 0;
	free(*buff);
	*buff = tmp;
	return (1);
}

static ssize_t	extract_from_buff(char **buff, int fd)
{
	ssize_t	count;

	if (*buff)
		return (gnl_strlen(*buff));
	*buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buff)
		return (-1);
	count = read(fd, *buff, BUFFER_SIZE);
	if (count < 1)
	{
		free(*buff);
		*buff = NULL;
		return (count);
	}
	(*buff)[count] = 0;
	return (gnl_strlen(*buff));
}

static int	line_concat(char **line, char *buff, size_t len)
{
	char	*tmp;
	size_t	i;

	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while (*line && (*line)[i])
	{
		tmp[i] = (*line)[i];
		i++;
	}
	while (*buff && *buff != '\n')
		tmp[i++] = *buff++;
	if (*buff == '\n')
		tmp[i++] = '\n';
	tmp[i] = 0;
	free(*line);
	*line = tmp;
	return (1);
}

int	read_line(char **buff, int fd, char **line)
{
	ssize_t	buff_len;
	size_t	line_len;
	int		is_line;

	buff_len = extract_from_buff(buff, fd);
	line_len = 0;
	while (buff_len > 0)
	{
		line_len += buff_len;
		is_line = line_concat(line, *buff, line_len);
		if (is_line < 1)
			return (is_line);
		if (manage_buff(buff, buff_len) < 0)
			return (-1);
		if ((*line)[line_len - 1] == '\n')
			return (1);
		buff_len = extract_from_buff(buff, fd);
	}
	return (buff_len);
}
