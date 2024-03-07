/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:52:48 by mben-yah          #+#    #+#             */
/*   Updated: 2024/03/07 10:57:27 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	const char	*p;

	p = str;
	if (!str)
		return (0);
	while (*p)
		p++;
	return (p - str);
}

int	newline_pos(char *data)
{
	int	pos;
	int	len;

	pos = 0;
	if (!data) 
		return (NOT_FOUND);
	len = ft_strlen(data);
	while (pos < len)
	{
		if (*(data + pos) == '\n')
			return (pos);
		pos++;
	}
	return (NOT_FOUND);
}

void	ft_clean(char **buff, char **next, char **garbage)
{
	free(*buff);
	*buff = 0;
	free(*next);
	*next = 0;
	free(*garbage);
	*garbage = 0;
}

int	ft_update(char **buff, char *next, char **garbage, int read_ret)
{
	int		nlen;
	char	*tmp;
	char	*tmp2;

	if (!next)
		return (0);
	if (read_ret)
		next[read_ret] = 0;
	nlen = newline_pos(next);
	if (nlen != NOT_FOUND)
	{
		tmp = ft_substr(next, 0, nlen + 1);
		*garbage = ft_strdup(next + nlen + 1);
		tmp2 = ft_strjoin(*buff, tmp);
		free(tmp);
	}
	else
		tmp2 = ft_strjoin(*buff, next);
	free(*buff);
	*buff = tmp2;
	if (!read_ret)
		free(next);
	if (!tmp2)
		return (ft_clean(garbage, garbage, buff), FAILURE);
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*next;
	int			read_ret;
	static char	*garbage;

	buff = NULL;
	next = garbage;
	garbage = NULL;
	ft_update(&buff, next, &garbage, 0);
	next = malloc(BUFFER_SIZE + 1);
	if (!next)
		return (ft_clean(&buff, &next, &garbage), NULL);
	while (newline_pos(buff) == NOT_FOUND) 
	{
		read_ret = read(fd, next, BUFFER_SIZE);
		if (!read_ret && ft_strlen(buff))
			return (ft_clean(&next, &next, &garbage), buff);
		if (read_ret == FAILURE || !read_ret)
			return (ft_clean(&buff, &next, &garbage), NULL);
		if (ft_update(&buff, next, &garbage, read_ret) == FAILURE)
			break ;
	}
	return (free(next), next = 0, buff);
}
