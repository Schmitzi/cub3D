/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:39:15 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

size_t	ft_nblen(int n)
{
	size_t	length;

	length = 0;
	if (n <= 0)
	{
		length++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int nb)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (nb == INT_MIN)
		return (ft_strndup("-2147483648", 11));
	len = ft_nblen(nb);
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = 0;
	if (nb < 0)
	{
		str[0] = '-';
		i++;
		nb *= -1;
	}
	while (len-- > i)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
