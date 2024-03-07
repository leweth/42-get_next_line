/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:09:06 by mben-yah          #+#    #+#             */
/*   Updated: 2024/03/07 10:24:46 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	dst_len = ft_strlen(dst);
	while (*(src + i) && i + dst_len < dstsize - 1)
	{
		*(dst + i + dst_len) = *(src + i);
		i++;
	}
	*(dst + i + dst_len) = 0;
}

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(s1);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (*(s1 + i) && i < len)
	{
		*(tmp + i) = *(s1 + i);
		i++;
	}
	*(tmp + i) = '\0';
	return (tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tmp = malloc(s1_len + s2_len + 1);
	if (!tmp)
		return (0);
	i = 0;
	while (*(s1 + i) && i < s1_len + s2_len)
	{
		*(tmp + i) = *(s1 + i);
		i++;
	}
	*(tmp + i) = '\0';
	ft_strlcat(tmp, s2, s1_len + s2_len + 1);
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(len + 1);
	if (!tmp)
		return (0);
	while (i < len)
		*(tmp + i++) = *(s++ + start);
	*(tmp + i) = 0;
	return (tmp);
}
