/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlst_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 04:37:20 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_strlst	*ft_strlst_new(char *str)
{
	t_strlst	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(1, sizeof(t_strlst));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	ft_strlst_push(t_strlst **head, t_strlst *item)
{
	t_strlst	*tmp;

	if (!head)
		return ;
	if (!*head)
	{
		*head = item;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = item;
}

void	ft_strlst_delete(t_strlst *node)
{
	if (!node)
		return ;
	if (node->str)
		free(node->str);
	free(node);
}

void	ft_strlst_clear(t_strlst **head)
{
	t_strlst	*tmp;
	t_strlst	*prev;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		ft_strlst_delete(prev);
	}
	*head = NULL;
}

size_t	ft_strlst_len(t_strlst *head)
{
	size_t	length;

	length = 0;
	while (head)
	{
		length++;
		head = head->next;
	}
	return (length);
}
