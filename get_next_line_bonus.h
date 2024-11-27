/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:11:22 by mpiantan          #+#    #+#             */
/*   Updated: 2024/11/27 16:12:27 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	char			*content;
}	t_list;

char	*get_next_line(int fd);
char	*get_line(t_list *list);

void	create_list(t_list **list, int fd);
void	add_element(t_list **list, char *buffer);
void	reset_list(t_list **list);
void	copy_content(t_list *list, char *str);
void	ft_free(t_list **list, t_list *clear_element, char *buffer);

int		newline_size(t_list *list);
int		found_newline(t_list *list);

t_list	*get_last_element(t_list *list);

#endif
