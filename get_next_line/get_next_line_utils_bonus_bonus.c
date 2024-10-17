/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:54:29 by xgossing          #+#    #+#             */
/*   Updated: 2024/08/29 18:14:50 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/get_next_line_bonus_bonus.h"

size_t	gnl_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strlen_char(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (c == '\0')
		return (i);
	if (s[i] == c)
		return (i + 1);
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s[0])
		return (NULL);
	while (s[i])
	{
		if ((char)s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*out;
	int		length;
	int		i;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	length = gnl_strlen(s1) + gnl_strlen(s2);
	out = malloc(length * sizeof(char) + 1);
	if (!out)
		return (NULL);
	temp = NULL;
	i = 0;
	temp = s1;
	while (*s1)
		out[i++] = *s1++;
	while (*s2)
		out[i++] = *s2++;
	free(temp);
	out[i] = '\0';
	return (out);
}

void	*gnl_calloc(size_t nmemb, size_t size)
{
	void	*out;
	size_t	i;

	if (nmemb > UINT_MAX || size > UINT_MAX)
		return (NULL);
	out = malloc(nmemb * size);
	if (!out)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((unsigned char *)out)[i] = '\0';
		i++;
	}
	return (out);
}
