/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:01:28 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:11 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && n > 0)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (s1[i] - s2[i]);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
		i++;
	ret = ft_calloc((i + 1), sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strndup_with_padding(const char *s, size_t len, size_t desired_len,
		char pad)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	ret = ft_calloc(desired_len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i] && i < len && i < desired_len)
	{
		ret[i] = s[i];
		i++;
	}
	while (i < desired_len)
	{
		ret[i] = pad;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_atoi(char *str)
{
	int64_t	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (-1);
	while (str[i] && is_one_of(str[i], "\t\n\v\r\f "))
		i++;
	if (str[i] && str[i] == '-')
		sign = -sign;
	if (str[i] && is_one_of(str[i], "+-"))
		i++;
	while (str[i] && is_digit(str[i]))
	{
		result = result * 10 + str[i++] - '0';
		if (result * sign > INT_MAX)
			return (-1);
		if (result * sign < INT_MIN)
			return (0);
	}
	return (result * sign);
}
