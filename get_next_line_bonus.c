/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:16 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/14 23:01:57 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
The function get_next_line will return a line read from a file descriptor one
by one.
Check_fd will check the fd and give acces to variable in the good node
or creat the node.
Free_node_if_empty free the node of the fd after read and return every line.
Line_and_remains change the remains and the len_rem, and finaly return the line.
Read_fd read the file descriptor and copy every buf in remains.
truncate -s -1 text
*/

t_fd_list	*check_fd(int fd, t_fd_list **list)
{
	t_fd_list	*current;
	t_fd_list	*new_list;

	current = *list;
	while (current != NULL && current->fd != fd)
		current = current->next;
	if (current == NULL)
	{
		new_list = (t_fd_list *)malloc(sizeof(t_fd_list));
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
		new_list->next = *list;
		return (*list = new_list, new_list);
	}
	return (current);
}

void	free_node_if_empty(int fd, t_fd_list *cursor)
{
	t_fd_list	*prev;
	t_fd_list	*current;

	prev = NULL;
	current = cursor;
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

char	*line_and_remains(t_fd_list *cursor)
{
	char	*line;
	int		len_nl;

	len_nl = (check_len(cursor->remains, 1));
	cursor->len_rem -= len_nl;
	if (check_len(cursor->remains, 0) == 0)
		return (NULL);
	line = malloc(sizeof(char) * len_nl);
	if (line == NULL)
		return (NULL);
	ft_strljoin(line, cursor->remains, len_nl + 1, 1);
	ft_strljoin(cursor->remains, &cursor->remains[len_nl], cursor->len_rem, 1);
	cursor->remains = ft_realloc(cursor->remains, cursor->len_rem);
	return (line);
}

void	read_fd(int fd, t_fd_list *cursor)
{
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	while (cursor->len_read > 0)
	{
		cursor->len_read = (int)read(fd, buf, BUFFER_SIZE);
		if (cursor->len_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[cursor->len_read] = '\0';
		cursor->len_rem += cursor->len_read;
		cursor->remains = ft_realloc(cursor->remains, cursor->len_rem);
		ft_strljoin(cursor->remains, buf, cursor->len_rem, 0);
		if (find_n(cursor->remains) == 1)
			break ;
	}
	free(buf);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*list;
	t_fd_list			*cursor;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	cursor = check_fd(fd, &list);
	if (cursor->len_read > 0)
		read_fd(fd, cursor);
	line = line_and_remains(cursor);
	if (cursor->len_read == 0 && cursor->len_rem == 0 && line == 0)
	{
		free_node_if_empty(fd, cursor);
		return (NULL);
	}
	return (line);
}

//int	main(void)
//{
//	int		fd;
//	//int		fd0;
//	//int		fd1;
//	//int		fd2;
//	//int		fd3;
//	char	*line;
//	int		i;
//	int		d;

//	line = NULL;
//	d = 0;
//	//fd0 = open("tripouille/files/41_with_nl", O_RDONLY);
//	//fd1 = open("tripouille/files/42_with_nl", O_RDONLY);
//	//fd2 = open("tripouille/files/43_with_nl", O_RDONLY);
//	//fd3 = open("tripouille/files/nl", O_RDONLY);

//	fd = open("tripouille/files/empty", O_RDONLY);
//	if (fd == -1)
//    {
//        perror("Error opening file");
//        return (1);
//    }
//	//if (fd0 == -1 || fd1 == -1 || fd2 == -1 || fd3 == -1)
//    //{
//    //    perror("Error opening file");
//    //    return (1);
//    //}
//	i = 0;
//	//printf("--------------- START MAIN fd0\n");
//	//line = get_next_line(fd0);
//	//d = printf("MAIN fd0 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd1\n");
//	//line = get_next_line(fd1);
//	//d = printf("MAIN fd1 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd2\n");
//	//line = get_next_line(fd2);
//	//d = printf("MAIN fd2 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd0\n");
//	//line = get_next_line(fd0);
//	//d = printf("MAIN fd0 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd1\n");
//	//line = get_next_line(fd1);
//	//d = printf("MAIN fd1 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd2\n");
//	//line = get_next_line(fd2);
//	//d = printf("MAIN fd2 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd0\n");
//	//line = get_next_line(fd0);
//	//d = printf("MAIN fd0 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd1\n");
//	//line = get_next_line(fd1);
//	//d = printf("MAIN fd1 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd2\n");
//	//line = get_next_line(fd2);
//	//d = printf("MAIN fd2 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd3\n");
//	//line = get_next_line(fd3);
//	//d = printf("MAIN fd3 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd3\n");
//	//line = get_next_line(fd3);
//	//d = printf("MAIN fd3 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);
//	//printf("--------------- START MAIN fd3\n");
//	//line = get_next_line(fd3);
//	//d = printf("MAIN fd3 -> %s\n", line);
//	//printf("NB char -- > %d\n", d);
//	//free(line);

//	while (i < 4)
//	{
//		line = get_next_line(fd);
//		if (line == NULL)
//		{
//			printf("BREAK MAIN\n");
//			break;
//		}
//		d = printf("MAIN -> %s\n", line);
//		printf("_________\n");
//		printf("NB char -- > %d\n", d);
//		free(line);
//		i++;
//	}
//	return (0);
//}
