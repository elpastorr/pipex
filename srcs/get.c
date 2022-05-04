/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:53:04 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/03 17:57:35 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char    *get_cmd(char **paths, char *cmd)
{
    char    *tmp;
    char    *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(command, X_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

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
    if (s)
    {
        while (s[i])
            write(1, &s[i++], 1);
    }
}
