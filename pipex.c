/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:32:09 by elpastor          #+#    #+#             */
/*   Updated: 2022/04/26 20:22:31 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_error(char *s)
{
    printf("%s", s);
    exit(1);
}

int main(int ac, char **av, char **env)
{
    t_env   myenv;

    if (ac != 5)
        ft_error("Arguments error\n");
    myenv.infile = open(av[1], O_RDONLY);
    if (myenv.infile < 0)
        ft_error("Infile error\n");
    myenv.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR);
    if (myenv.outfile < 0)
        ft_error("Outfile error\n");
    if (pipe(myenv.pipe) < 0)
        ft_error("Pipe error\n");
    myenv.paths = ft_split(get_path(env), ':');
    myenv.pid1 = fork();
    if (myenv.pid1 == 0)
    //Premiere cmd
    myenv.pid2 = fork();
    if (myenv.pid2 == 0)
    //Deuxieme cmd
}