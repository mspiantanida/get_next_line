/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:38:08 by mpiantan          #+#    #+#             */
/*   Updated: 2024/11/26 18:51:19 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_last_element(t_list *list)
{
	t_list	*last_element;

	last_element = list;
	if (!last_element)
		return (NULL);
	while (last_element->next)
		last_element = last_element->next;
	return (last_element);
}

int	newline_size(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	copy_content(t_list *list, char *str)
{
	int	i;
	int	k;

	k = 0;
	if (!list)
		return ;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
			}
			str[k++] = list->content[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

int     found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void    ft_free(t_list **list, t_list *clear_element, char *buffer)
{
	t_list	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
	}
	*list = NULL;
	if(clear_element->content[0])
		*list = clear_element;
	else
	{
		free(buffer);
		free(clear_element);
	}
}
