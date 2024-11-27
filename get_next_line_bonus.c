/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:39:04 by mpiantan          #+#    #+#             */
/*   Updated: 2024/11/27 17:43:28 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	reset_list(t_list **list)
{
	t_list	*last_element;
	t_list	*clear_element;
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = (char *) malloc (BUFFER_SIZE + 1);
	clear_element = (t_list *) malloc (sizeof(t_list));
	if (!buffer || !clear_element)
		return ;
	last_element = get_last_element (*list);
	while (last_element->content[i] != '\0' && last_element->content[i] != '\n')
		i++;
	while (last_element->content[i] != '\0' && last_element->content[++i])
		buffer[j++] = last_element->content[i];
	buffer[j] = '\0';
	clear_element->content = buffer;
	clear_element->next = NULL;
	ft_free(list, clear_element, buffer);
}

char	*get_line(t_list *list)
{
	char	*next_str;
	int		str_len;

	if (!list)
		return (NULL);
	str_len = newline_size(list);
	next_str = (char *) malloc (str_len + 1);
	if (!next_str)
		return (NULL);
	copy_content (list, next_str);
	return (next_str);
}

void	add_element(t_list **list, char *buffer)
{
	t_list	*new_element;
	t_list	*last_element;

	last_element = get_last_element (*list);
	new_element = (t_list *) malloc (sizeof(t_list));
	if (!new_element)
		return ;
	if (last_element == NULL)
		*list = new_element;
	else
		last_element->next = new_element;
	new_element->content = buffer;
	new_element->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	char	*buffer;
	int		chars_read;

	while (!found_newline(*list))
	{
		buffer = (char *) malloc (BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		chars_read = read (fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free (buffer);
			buffer = NULL;
			return ;
		}
		buffer[chars_read] = '\0';
		add_element (list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*next_line;

	if (fd < 0 || fd < 0 || fd > 1023)
		return (NULL);
	create_list (&list[fd], fd);
	if (!list[fd])
		return (NULL);
	next_line = get_line (list[fd]);
	reset_list(&list[fd]);
	return (next_line);
}

/*#include <stdio.h>

int	main(int argc, char **argv)
{
	int	*fd;
	char	**lines;
	int	*finished;
	int	total_files;
	int	i;
	int	all_finished;	

	if (argc < 2)
	{
		printf("Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
		return (1);
	}
	total_files = argc - 1;
	fd = malloc(sizeof(int) * total_files);
	lines = malloc(sizeof(char *) * total_files);
	finished = malloc(sizeof(int) * total_files);
	if (!fd || !lines || !finished)
	{
		printf("Memory allocation error. \n");
		return (1);
	}
	i = 0;
	while (i < total_files)
	{
		fd[i] = open (argv[i + 1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error opening file: %s\n", argv[i + 1]);
			while (--i >= 0)
				close(fd[i]);
			free(fd);
			free(lines);
			free(finished);
			return (1);
		}
		lines[i] = NULL;
		finished[i] = 0;
		i++;
	}
	all_finished = 0;
	while (!all_finished)
	{
		all_finished = 1;
		i = 0;
		while (i < total_files)
		{
			if (!finished[i] && (lines[i] = get_next_line(fd[i])))
			{
				printf("File %d->%s", i + 1, lines[i]);
				free(lines[i]);
				all_finished = 0;
			}
			else if (!finished[i])
			{
				finished[i] = 1;
			}
			i++;
		}
	}
	i = 0;
	while (i < total_files)
	{
		close(fd[i]);
		i++;
	}
	free(fd);
	free(lines);
	free(finished);

	return (0);
}*/
