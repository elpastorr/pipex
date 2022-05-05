/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:54:50 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/05 19:09:23 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

void    ft_putstr(char *s)
{
    int i;

    i = 0;
    if (!s)
        return ;
    while (s[i])
        write(1, &s[i++], 1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	dst = malloc(count * size);
	if (dst == NULL)
		return (dst);
    ft_bzero(dst, count * size);
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;

	tmp = s;
	while (n--)
		*tmp++ = 0;
}
