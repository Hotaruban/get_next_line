/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:12 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/16 00:43:08 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
Ft_realloc reallocate memory to the pointeur of size.
Check_len count the len of the string depending of parameter 0 for find '\0'
and 1 for '\n'.
Find_n find the '\n' in a string.
Ft_strljoin concatenate if the parameter action = 0 or copy if he is not.
*/

char	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	char	*src;
	char	*dst;

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
		free (ptr);
		return (NULL);
	}
	src = (char *)ptr;
	dst = (char *)new_ptr;
	while (size--)
		*dst++ = *src++;
	free(ptr);
	return (new_ptr);
}

size_t	check_len(char *s, char c)
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

void	ft_strljoin(char *dst, const char *src, size_t dstsize, int c)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;

	dstlen = check_len(dst, c);
	i = 0;
	j = dstlen;
	if (c == '\0')
	{
		while (src[i] != '\0' && i < (dstsize - dstlen - 1))
			dst[j++] = (char)src[i++];
		dst[j] = '\0';
	}
	else
	{
		while ((src[i] != '\0') && (i != dstsize - 1))
		{
			dst[i] = (char)src[i];
			i++;
		}
		dst[i] = '\0';
	}
}
