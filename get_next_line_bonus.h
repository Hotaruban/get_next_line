/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:02:25 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/14 22:49:04 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct fd_list
{
	int				fd;
	char			*remains;
	int				len_rem;
	int				len_read;
	struct fd_list	*next;
}					t_fd_list;

char		*get_next_line(int fd);
t_fd_list	*check_fd(int fd, t_fd_list **list);
t_fd_list	*free_node_if_empty(int fd, t_fd_list **cursor);
char		*line_and_remains(t_fd_list *cursor);
void		read_fd(int fd, t_fd_list *cursor);

void		*ft_realloc(void *ptr, size_t old_size, size_t size);
size_t		ft_strlen(const char *s, char c);
void		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			find_n(char *s);

#endif