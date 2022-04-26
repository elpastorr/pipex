/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:18:06 by elpastor          #+#    #+#             */
/*   Updated: 2022/04/26 20:20:35 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_env {
    int     pipe[2];    
    char    *cmd;
    char    **paths;
    char    **cmd_args;
    int     infile;
    int     outfile;
    pid_t   pid1;
    pid_t   pid2;
}   t_env;

size_t          ft_strlen(const char *s);
char	        *ft_strjoin(char const *s1, char const *s2);
static size_t	countchar(char const *s, char c);
static size_t   countword(char const *s, char c);
char            **ft_split(char const *s, char c);


#endif