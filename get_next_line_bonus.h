/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:02:25 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/16 00:36:27 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
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
t_fd_list	*find_node(int fd, t_fd_list **list);
t_fd_list	*free_node_if_empty(int fd, t_fd_list **list);
char		*line_and_remains(t_fd_list *cursor);
void		read_fd(int fd, t_fd_list *cursor);

char		*ft_realloc(void *ptr, size_t size);
size_t		check_len(char *s, char c);
int			find_n(char *s);
void		ft_strljoin(char *dst, const char *src, size_t dstsize, int action);

#endif
