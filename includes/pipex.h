/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:18:06 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/03 17:51:13 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_env {
	int		pipe[2];
	char	*cmd;
	char	**paths;
	char	**cmd_args;
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
}	t_env;

void			ft_error(char *s);
void			first_cmd(t_env myenv, char **av, char **env);
void			second_cmd(t_env myenv, char **av, char **env);

size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
// static size_t	countchar(char const *s, char c);
// static size_t	countword(char const *s, char c);
char			**ft_split(char const *s, char c);


char			*get_cmd(char **paths, char *cmd);
char			*get_path(char **env);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
void			ft_putstr(char *s);


#endif