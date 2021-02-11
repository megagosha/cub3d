/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:14:36 by edebi             #+#    #+#             */
/*   Updated: 2020/12/02 16:21:21 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTGET_NEXT_LINE_H
# define FTGET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE = 64
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

size_t			ft_strlen(const char *str);
char			*gnl_strdup(const char *s1, int i);
int				get_next_line(int fd, char **line);
#endif
