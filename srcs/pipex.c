/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:32:09 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/05 19:11:16 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_free(char *s, t_env *myenv)
{
    int i;

    ft_putstr(s);
    i = 0;
    if (myenv->pid1 != 0 && myenv->pid2 != 0)
    {
        while (myenv->paths[i])
            free(myenv->paths[i++]);
        free(myenv->paths);
        close(myenv->infile);
        close(myenv->outfile);
         free(myenv);
    }
    if (myenv->pid1 == 0 || myenv->pid2 == 0)
    {
        i = 0;
        while (myenv->cmd_args[i])
            free(myenv->cmd_args[i++]);
        free(myenv->cmd_args);
    }
    exit(1);
}

void    ft_error(char *s)
{
    printf("%s", s);
    exit(1);
}

void    first_cmd(t_env *myenv, char **av, char **env)
{
    close(myenv->pipe[0]);
    dup2(myenv->infile, 0);
    myenv->cmd_args = ft_split(av[2], ' ');
    myenv->cmd = get_cmd(myenv->paths, myenv->cmd_args[0]);
    if (myenv->cmd == NULL)
        ft_free("First command error\n", myenv);
    dup2(myenv->pipe[1], 1);
    execve(myenv->cmd, myenv->cmd_args, env);
}

void    second_cmd(t_env *myenv, char **av, char **env)
{
    close(myenv->pipe[1]);
    dup2(myenv->pipe[0], 0);
    myenv->cmd_args = ft_split(av[3], ' ');
    myenv->cmd = get_cmd(myenv->paths, myenv->cmd_args[0]);
    if (myenv->cmd == NULL)
        ft_free("Second command error\n", myenv);
    dup2(myenv->outfile, 1);
    execve(myenv->cmd, myenv->cmd_args, env);
}

void    init_myenv(t_env *myenv, int ac, char **av, char **env)
{
    myenv->paths = ft_split(get_path(env), ':');
    myenv->infile = open(av[1], O_RDONLY);
    if (myenv->infile < 0)
        ft_free("Infile error\n", myenv);
    myenv->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    if (myenv->outfile < 0)
        ft_free("Outfile error\n", myenv);
    if (pipe(myenv->pipe) < 0)
        ft_free("Pipe error\n", myenv);
}

int main(int ac, char **av, char **env)
{
    t_env   *myenv;

    if (ac != 5)
        ft_error("Arguments error\n");
    if (!env[0])
        ft_error("Environnement error\n");
    myenv = ft_calloc(1, sizeof(t_env));
    init_myenv(myenv, ac, av, env);
    myenv->pid1 = fork();
    if (myenv->pid1 == 0)
        first_cmd(myenv, av, env);
    myenv->pid2 = fork();
    if (myenv->pid2 == 0)
        second_cmd(myenv, av, env);
    close(myenv->pipe[0]);
    close(myenv->pipe[1]);
    waitpid(myenv->pid1, NULL, 0);
    waitpid(myenv->pid2, NULL, 0);
    ft_free(NULL, myenv);
    return (0);
}
