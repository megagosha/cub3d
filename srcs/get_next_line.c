/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:40:24 by edebi             #+#    #+#             */
/*   Updated: 2020/12/02 16:21:10 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if ((str = malloc(sizeof(char) * (len_s1 + len_s2 + 2))) == NULL)
		return ((char *)0);
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int		check_new_line(const char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		read_line(char **str, char **hist, int fd)
{
	int		bytes;
	int		i;
	char	buf[BUFFER_SIZE + 1];
	char	*del;

	i = -1;
	while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		del = *str;
		*str = gnl_strjoin(*str, buf);
		if ((i = check_new_line(*str)) != -1)
		{
			*hist = *str;
			free(del);
			return (i);
		}
		if (del != NULL)
			free(del);
	}
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (-2);
	return (i);
}

int		return_line(char **line, char **str, int i, char **hist)
{
	int		j;
	char	*tmp;

	j = ft_strlen(*str);
	if ((*line = gnl_strdup(*str, i)) == NULL)
		return (-1);
	(*line)[i] = '\0';
	tmp = *str;
	if ((*str = gnl_strdup((*str) + i + 1, j - i + 1)) == NULL)
		return (-1);
	(*str)[j - i + 1] = '\0';
	*hist = *str;
	free(tmp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			i;
	static char	*buf[4096];
	char		*str;

	str = NULL;
	if ((line == NULL || read(fd, str, 0) < 0) != 0)
		return (-1);
	str = buf[fd] ? buf[fd] : str;
	if ((i = check_new_line(str)) == -1)
		i = read_line(&str, &(buf[fd]), fd);
	if (i == -2)
	{
		if (str != NULL)
		{
			*line = gnl_strdup(str, 0);
			free(str);
		}
		else
			*line = gnl_strdup("\0", 1);
		buf[fd] = NULL;
		return (0);
	}
	if (i < 0)
		return (-1);
	return (return_line(line, &str, i, &(buf[fd])));
}
