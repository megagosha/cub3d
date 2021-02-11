/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:21:05 by edebi             #+#    #+#             */
/*   Updated: 2020/12/02 16:21:20 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strdup(const char *s1, int i)
{
	size_t	len_str;
	char	*str;
	size_t	j;

	j = 0;
	if (i == 0)
		len_str = ft_strlen(s1);
	else
		len_str = i;
	str = malloc(sizeof(char) * (len_str + 1));
	if (str == NULL)
		return ((char *)0);
	while (j < len_str)
	{
		str[j] = s1[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
