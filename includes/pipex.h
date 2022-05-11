/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:18:06 by elpastor          #+#    #+#             */
/*   Updated: 2022/05/11 13:02:24 by elpastor         ###   ########.fr       */
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

void	first_cmd(t_env *myenv, char **av, char **env);
void	second_cmd(t_env *myenv, char **av, char **env);
void	init_myenv(t_env *myenv, int ac, char **av, char **env);

int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		countchar(char const *s, char c);
int		countword(char const *s, char c);

char	*get_cmd(char **paths, char *cmd);
char	*get_path(char **env);
void	ft_free2(t_env *myenv, int i);
void	ft_free(char *s, t_env *myenv);
void	ft_error(char *s);

int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	ft_putstr(char *s);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif