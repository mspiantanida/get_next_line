/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:39:04 by mpiantan          #+#    #+#             */
/*   Updated: 2024/11/26 18:55:41 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	last_element = get_last_element (*list);//ft_lstlast
	while (last_element->content[i] && last_element->content[i] != '\0')
		i++;
	while (last_element->content[i] && last_element->content[i++])
		buffer[j++] = last_element->content[i];
	buffer[j] = '\0';
	clear_element->content = buffer;
	clear_element->next = NULL;
	ft_free(list, clear_element, buffer);//ft_free
}

char	*get_line(t_list *list)
{
	char	*next_str;
	int		str_len;

	if (!list)
		return (NULL);
	str_len = newline_size(list); //ft_lstsize
	next_str = (char *) malloc (str_len + 1);
	if (!next_str)
		return (NULL);
	copy_content (list, next_str); //ft_strcpy
	return (next_str);
}

void	add_element(t_list **list, char *buffer)
{
	t_list	*new_element;
	t_list	*last_element;

	last_element = get_last_element (*list); // ft_lstlast
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

	while (!found_newline(*list)) //ft_newline
	{
		buffer = (char *) malloc (BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		chars_read = read (fd, buffer, BUFFER_SIZE);
		if (!chars_read)
		{
			free (buffer);
			return ;
		}
		buffer[chars_read] = '\0';
		add_element (list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list (&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line (list);
	reset_list(&list);
	return (next_line);
}


#include <stdio.h>

int	main(void)
{
}
