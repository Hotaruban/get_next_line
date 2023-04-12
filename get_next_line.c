/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:16 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/12 22:30:58 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// function check_fd will check the fd and give acces to variable in the good node or creat the node
t_fd_list	*check_fd(int fd, t_fd_list *list)
{
	t_fd_list	*current = NULL;
	t_fd_list	*new_list;

	while (current != NULL && current->fd != fd)
		current = current->next;
	if (current == NULL)
	{
	    new_list = (t_fd_list*)malloc(sizeof(t_fd_list));
		if (new_list == NULL)
			return (NULL);
        new_list->fd = fd;
        new_list->remains = malloc(sizeof(char) * 1);
		if (new_list->remains == NULL)
		{
			free(new_list);
			return (NULL);
		}
		new_list->remains[0] = '\0';
        new_list->len_rem = 1;
		new_list->len_read = 1;
        new_list->next = list;
        current = new_list;
	}
	return (current);
}

// function free_node_if_empty free the node of the fd after read and return every line.
void	free_node_if_empty(int fd, t_fd_list *cursor)
{
	t_fd_list *prev = NULL;
	t_fd_list *current = cursor;

	while (current != NULL && current->fd != fd)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL && current->len_rem == 0 && current->len_read == 0)
	{
		if (prev == NULL)
			prev = current->next;
		else
			prev->next = current->next;
		free(current->remains);
		free(current);
	}
}

// function line_and_remains change the remains and the len_rem, and finaly return the line
char	*line_and_remains(t_fd_list *cursor)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * cursor->len_rem);
	if (line == NULL)
		return (NULL);
	i = check_len(cursor->remains, '\n') + 2;
	ft_strljoin(line, cursor->remains, i, 0);
	ft_strljoin(cursor->remains, &cursor->remains[i], cursor->len_rem, 0);
	cursor->len_rem -= i;
	ft_realloc(cursor->remains, cursor->len_rem);
	return (line);
}

// function read_fd read the file descriptor and copy every buf in remains
void	read_fd(int fd, t_fd_list *cursor)
{
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	while (check_len(cursor->remains, '\n') == 0 && cursor->len_read != 0)
	{
		cursor->len_read = (int)read(fd, buf, BUFFER_SIZE);
		if ((cursor->len_read) == -1)
		{
			free(buf);
			return ;
		}
		buf[(cursor->len_read)] = '\0';
		cursor->len_rem += cursor->len_read;
		ft_realloc(cursor->remains, cursor->len_rem);
		ft_strljoin(cursor->remains, buf, cursor->len_rem, 1);
	}
	free(buf);
}

// function get_next_line return a pointeur of the line read in fd
char	*get_next_line(int fd)
{
	static t_fd_list	*list = NULL;
	t_fd_list			*cursor;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	cursor = check_fd(fd, list);
	printf("BUG-002\n");
	if (cursor->len_read > 0)
		read_fd(fd, cursor);
			printf("BUG-003\n");
	line = line_and_remains(cursor);
	printf("BUG-004\n");
	free_node_if_empty(fd, cursor);
	return (line);
}

// function main who open text.txt and print the line return by get_next_line
int	main(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("get_next_line.c", O_RDONLY);
	if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}
