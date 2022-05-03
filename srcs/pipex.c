/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:32:09 by elpastor          #+#    #+#             */
/*   Updated: 2022/04/28 17:28:20 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_error(char *s, t_env myenv)
{
    int i;

    printf("%s", s);
    i = 0;
    if (myenv.cmd_args)
    {
        while (myenv.cmd_args[i])
		    free(myenv.cmd_args[i++]);
	    free(myenv.cmd_args);
    }
    if (myenv.cmd)
        free(myenv.cmd);
    exit(1);
}

void    ft_free(t_env myenv)
{
    int i;

    i = 0;
    while (myenv.paths[i])
        free(myenv.paths[i++]);
    free(myenv.paths);
    i = 0;
    while (myenv.cmd_args[i])
        free(myenv.cmd_args[i++]);
    close(myenv.infile);
    close(myenv.outfile);
}

void    first_cmd(t_env myenv, char **av, char **env)
{
    close(myenv.pipe[0]);
    dup2(myenv.pipe[1], 1);
    dup2(myenv.infile, 0);
    myenv.cmd_args = ft_split(av[2], ' ');
    myenv.cmd = get_cmd(myenv.paths, myenv.cmd_args[0]);
    if (myenv.cmd == NULL)
        ft_error("First command error\n", myenv);
    execve(myenv.cmd, myenv.cmd_args, env);
}

void    second_cmd(t_env myenv, char **av, char **env)
{
    close(myenv.pipe[1]);
    dup2(myenv.pipe[0], 0);
    dup2(myenv.outfile, 1);
    myenv.cmd_args = ft_split(av[3], ' ');
    myenv.cmd = get_cmd(myenv.paths, myenv.cmd_args[0]);
    if (myenv.cmd == NULL)
        ft_error("Second command error\n", myenv);
    execve(myenv.cmd, myenv.cmd_args, env);
}

int main(int ac, char **av, char **env)
{
    t_env   myenv;

    if (ac != 5)
    {
        printf("Arguments error\n");
        exit(1);
    }
    myenv.infile = open(av[1], O_RDONLY);
    if (myenv.infile < 0)
        ft_error("Infile error\n", myenv);
    myenv.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    if (myenv.outfile < 0)
    {
        printf("fd = %d\n", myenv.outfile);
        ft_error("Outfile error\n", myenv);
    }
    if (pipe(myenv.pipe) < 0)
        ft_error("Pipe error\n", myenv);
    myenv.paths = ft_split(get_path(env), ':');
    myenv.pid1 = fork();
    if (myenv.pid1 == 0)
        first_cmd(myenv, av, env);
    myenv.pid2 = fork();
    if (myenv.pid2 == 0)
        second_cmd(myenv, av, env);
    close(myenv.pipe[0]);
    close(myenv.pipe[1]);
    waitpid(myenv.pid1, NULL, 0);
    waitpid(myenv.pid2, NULL, 0);
    ft_free(myenv);
    return (0);
}