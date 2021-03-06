/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:53:04 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/11 13:00:25 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

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
	while (*env && ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	ft_free2(t_env *myenv, int i)
{
	while (myenv->cmd_args[i])
		free(myenv->cmd_args[i++]);
	free(myenv->cmd_args);
	i = 0;
	while (myenv->paths[i])
		free(myenv->paths[i++]);
	free(myenv->paths);
	free(myenv);
}

void	ft_free(char *s, t_env *myenv)
{
	int	i;

	ft_putstr(s);
	i = 0;
	if (myenv->pid1 != 0 && myenv->pid2 != 0)
	{
		while (myenv->paths[i])
			free(myenv->paths[i++]);
		free(myenv->paths);
		if (myenv->infile != -1)
			close(myenv->infile);
		if (myenv->outfile != -1)
			close(myenv->outfile);
		free(myenv);
	}
	else
		ft_free2(myenv, i);
	exit(0);
}

void	ft_error(char *s)
{
	ft_putstr(s);
	exit(1);
}
