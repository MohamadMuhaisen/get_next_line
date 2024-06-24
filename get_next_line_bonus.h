/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:28:31 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/06/21 00:11:43 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

int		has_newline(t_list *list);
t_list	*get_last_node(t_list *list);
char	*extract_line(t_list *list);
void	copy_to_buffer(t_list *list, char *buffer);
int		get_length_to_newline(t_list *list);
void	clean_list(t_list **list);
char	*get_next_line(int fd);
void	free_list(t_list **list, t_list *new_node);
void	build_list(t_list **list, int fd);
void	add_node(t_list **list, char *buf, int fd);

#endif
