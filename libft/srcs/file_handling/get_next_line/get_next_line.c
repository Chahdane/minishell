/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:05:16 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 18:01:24 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*get_file(t_file **tracker, int fd)
{
	t_file	*ptr;

	if (fd < 0)
		return (NULL);
	ptr = *tracker;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	}
	ptr = malloc(sizeof(t_file));
	if (!ptr)
		return (NULL);
	ptr->fd = fd;
	ptr->buff = NULL;
	ptr->next = *tracker;
	*tracker = ptr;
	return (ptr);
}

static void	clear_file(t_file **tracker, t_file *file)
{
	t_file	*ptr;

	if (*tracker == file)
		*tracker = (*tracker)->next;
	else
	{
		ptr = *tracker;
		while (ptr->next && ptr->next != file)
			ptr = ptr->next;
		ptr->next = file->next;
	}
	if (file->buff)
		free(file->buff);
	free(file);
}

char	*get_next_line(int fd)
{
	static t_file	*tracker;
	char			*line;
	t_file			*file;
	int				is_line;

	line = NULL;
	file = get_file(&tracker, fd);
	if (!file)
		return (NULL);
	is_line = read_line(&(file->buff), file->fd, &line);
	if (is_line < 1)
	{
		clear_file(&tracker, file);
		if (is_line < 0)
		{
			free(line);
			line = NULL;
		}
	}
	return (line);
}
