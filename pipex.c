/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:32:09 by elpastor          #+#    #+#             */
/*   Updated: 2022/04/27 18:17:25 by elpastor         ###   ########.fr       */
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
        if (access(command, F_OK) == 0)
            return (command);
        free(command);
        paths++;
    }
    return (NULL);
}

void    ft_error(char *s)
{
    printf("%s", s);
    exit(1);
}

char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void    writing_child(t_env myenv, char **av, char **env)
{
    close(myenv.pipe[0]);
    dup2(myenv.pipe[1], 1);
    dup2(myenv.infile, 0);
    myenv.cmd_args = ft_split(av[2], ' ');
    myenv.cmd = get_cmd(myenv.paths, myenv.cmd_args[0]);
    if (myenv.cmd == NULL)
        ft_error("First command error\n");
    execve(myenv.cmd, myenv.cmd_args, env);
}

void    reading_child(t_env myenv, char **av, char **env)
{
    close(myenv.pipe[1]);
    dup2(myenv.pipe[0], 0);
    dup2(myenv.outfile, 1);
    myenv.cmd_args = ft_split(av[3], ' ');
    myenv.cmd = get_cmd(myenv.paths, myenv.cmd_args[0]);
    if (myenv.cmd == NULL)
        ft_error("Second command error\n");
    execve(myenv.cmd, myenv.cmd_args, env);
}

int main(int ac, char **av, char **env)
{
    t_env   myenv;

    if (ac != 5)
        ft_error("Arguments error\n");
    myenv.infile = open(av[1], O_RDONLY);
    if (myenv.infile < 0)
        ft_error("Infile error\n");
    myenv.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    if (myenv.outfile < 0)
    {
        printf("fd = %d\n", myenv.outfile);
        ft_error("Outfile error\n");
    }
    if (pipe(myenv.pipe) < 0)
        ft_error("Pipe error\n");
    myenv.paths = ft_split(get_path(env), ':');
    myenv.pid1 = fork();
    if (myenv.pid1 == 0)
        writing_child(myenv, av, env);
    myenv.pid2 = fork();
    if (myenv.pid2 == 0)
        reading_child(myenv, av, env);
    return (0);
}