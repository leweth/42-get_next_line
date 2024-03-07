/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:38:23 by mben-yah          #+#    #+#             */
/*   Updated: 2024/03/07 10:25:28 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_strlcat(char *dst, const char *src, size_t dstsize, size_t dst_len)
{
	size_t	i;
	size_t	limit;

	i = 0;
	limit = dstsize - 1;
	dst = dst + dst_len;
	while (*(src + i) && i + dst_len < limit)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = 0;
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
	while (i < len)
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
	size_t	i;
	size_t	sum;
	size_t	s2_len;
	size_t	s1_len;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	s2_len = ft_strlen(s2);
	s1_len = ft_strlen(s1);
	sum = s1_len + s2_len;
	tmp = malloc(sum + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(tmp + i) = *(s1 + i);
		i++;
	}
	*(tmp + i) = '\0';
	ft_strlcat(tmp, s2, sum + 1, s1_len);
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	s = s + start;
	while (i < len)
		*(tmp + i++) = *(s++);
	*(tmp + i) = 0;
	return (tmp);
}
