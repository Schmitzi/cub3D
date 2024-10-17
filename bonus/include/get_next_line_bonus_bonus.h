/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_bonus.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:39:36 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:44 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_BONUS_H
# define GET_NEXT_LINE_BONUS_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*gnl_strchr(const char *source, int c);
char	*gnl_strjoin(char *target, char *source);
size_t	gnl_strlen(const char *s);
void	*gnl_calloc(size_t nmemb, size_t size);
size_t	gnl_strlen_char(char *s, char c);

char	*get_next_line(int fd);
void	read_line(int fd, char **remainder);
char	*get_clean_line(char *line);
char	*trim_rest(char *line);
char	*free_and_null(char *str);

#endif
