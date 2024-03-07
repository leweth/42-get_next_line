/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:52:48 by mben-yah          #+#    #+#             */
/*   Updated: 2024/03/07 10:26:19 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		return (-1);
	len = ft_strlen(data);
	while (pos < len)
	{
		if (*(data + pos) == '\n')
			return (pos);
		pos++;
	}
	return (-1);
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
	if (nlen != -1)
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
		return (ft_clean(buff, garbage, garbage), -2);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*next;
	int			read_ret;
	static char	*garbage[OPEN_MAX];

	buff = NULL;
	next = *(garbage + fd);
	*(garbage + fd) = NULL;
	ft_update(&buff, next, garbage + fd, 0);
	next = malloc(BUFFER_SIZE + 1);
	if (!next)
		return (ft_clean(&buff, &next, garbage + fd), NULL);
	while (newline_pos(buff) == -1) 
	{
		read_ret = read(fd, next, BUFFER_SIZE);
		if (!read_ret && ft_strlen(buff))
			return (ft_clean(&next, &next, garbage + fd), buff);
		if (read_ret == -1 || !read_ret)
			return (ft_clean(&buff, &next, garbage + fd), NULL);
		else
			read_ret = ft_update(&buff, next, garbage + fd, read_ret);
		if (read_ret == -2)
			break ;
	}
	return (free(next), next = 0, buff);
}
