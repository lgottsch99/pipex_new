/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:10:31 by lgottsch          #+#    #+#             */
/*   Updated: 2024/11/14 17:38:16 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include "./full_libft/full_libft.h"
#include <sys/types.h> //fork
#include <sys/wait.h> //wait
#include <fcntl.h> //open
#include <errno.h> //perror
//#include <fcntl.h> //permissions open()

//pipex.c
int     check_in(char *file);

//children.c
void    kid1(int fd0, int fd1, char *argv[], char *envp[]);
void    kid2(int fd0, int fd1, char *argv[], char *envp[]);


//execute.c
char    **get_path(char *envp[]);
char    *get_exec_path(char *cmd, char **path);
void    exec_cmd(char *cmd, char *envp[]);



//pipex_help.c


#endif