/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:16 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/12 17:07:33 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// function check_fd will check the fd and give acces to variable in the good node or creat the node
void	check_fd(int fd, char *remains, int *len_rem, int *len_read, t_fd_list *list)
{
	t_fd_list *current = list;
	while (current != NULL && current->fd != fd)
		current = current->next;
	if (current == NULL)
	{
	    current = (t_fd_list*)malloc(sizeof(t_fd_list));
		if (current == NULL)
			return ;
        current->fd = fd;
        current->remains = malloc(sizeof(char) * 1);
		if (current->remains == NULL)
		{
			free(current);
			return ;
		}
		current->remains[0] = '\0';
        current->len_rem = 1;
		current->len_read = 1;
        current->next = list;
        list = current;
	}
	*remains = *current->remains;
	*len_rem = current->len_rem;
	*len_read = current->len_read;
}

// function free_node_if_empty free the node of the fd after read and return every line.
void	free_node_if_empty(int fd, t_fd_list **list)
{
	t_fd_list *prev = NULL;
	t_fd_list *current = *list;

	while (current != NULL && current->fd != fd)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL && current->len_rem == 0 && current->len_read == 0)
	{
		if (prev == NULL)
			list = &current->next;
		else
			prev->next = current->next;
		free(current->remains);
		free(current);
	}
}

// function line_and_remains change the remains and the len_rem, and finaly return the line
char	*line_and_remains(char **remains, int *len_rem)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (*len_rem));
	if (line == NULL)
		return (NULL);
	i = check_len(*remains, '\n') + 2;
	ft_strljoin(line, *remains, i, 0);
	ft_strljoin(*remains, remains[i], (*len_rem), 0);
	*len_rem -= i;
	ft_realloc((void **)&remains, (*len_rem));
	return (line);
}

// function read_fd read the file descriptor and copy every buf in remains
void	read_fd(int fd, char **remains, int *len_rem, int *len_read)
{
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	while (check_len(*remains, '\n') == 0 && len_read != 0)
	{
		*len_read = (int)read(fd, buf, BUFFER_SIZE);
		if ((*len_read) == -1)
		{
			free(buf);
			return ;
		}
		buf[(*len_read)] = '\0';
		*len_rem += *len_read;
		ft_realloc((void **)&remains, *len_rem);
		ft_strljoin(*remains, buf, (*len_rem), 1);
	}
	free(buf);
}

// function get_next_line return a pointeur of the line read in fd
char	*get_next_line(int fd)
{
	static t_fd_list	*list = NULL;
	char				*remains;
	int					*len_rem;
	int					*len_read;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);

	remains = NULL;
	len_rem = NULL;
	len_read = NULL;
	check_fd(fd, remains, len_rem, len_read, list);
	if (len_read > 0)
		read_fd(fd, &remains, len_rem, len_read);
	line = line_and_remains(&remains, len_rem);
	free_node_if_empty(fd, &list);
	return (line);
}

// function main who open text.txt and print the line return by get_next_line
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
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
