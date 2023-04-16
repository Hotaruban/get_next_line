/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:12 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/16 22:31:37 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void			*new_ptr;
	unsigned char	*src;
	unsigned char	*dst;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	src = (unsigned char *)ptr;
	dst = (unsigned char *)new_ptr;
	if (old_size <= size)
		size = old_size;
	while (size--)
		*dst++ = *src++;
	free(ptr);
	return (new_ptr);
}

size_t	ft_strlen(const char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	if (c == 0)
	{
		while (s[i] != '\0')
			i++;
	}
	else
	{
		while (s[i] && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			i++;
	}
	return (i);
}

int	find_n(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;

	dstlen = ft_strlen(dst, 0);
	i = 0;
	j = dstlen;
	while (src[i] != 0 && i < (dstsize - dstlen - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
}

void	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (src == NULL)
	{
		dst[0] = '\0';
		return ;
	}
	while (src[i] != '\0' && (i != dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
