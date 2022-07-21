/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:05:28 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 13:32:32 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

typedef struct s_file
{
	int				fd;
	char			*buff;
	struct s_file	*next;
}		t_file;

int		read_line(char **buff, int fd, char **line);
char	*get_next_line(int fd);

#endif
