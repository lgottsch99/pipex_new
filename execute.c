/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:59:32 by lgottsch          #+#    #+#             */
/*   Updated: 2024/11/14 17:38:15 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char **get_path(char *envp[]) //find path in envp and extract full path
{
	int i;
	char *fullpath;
    char **paths;
	
	i = 0;
	while (envp[i])
	{
		//ft_printf("%s\n", envp[i]);
		if ((ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))!= NULL)
		{
			if (envp[i][0]== 'P' && envp[i][1]== 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
			{
				fullpath = ft_substr(envp[i], 5, (ft_strlen(envp[i]))); // !!!!malloc
                paths = ft_split(fullpath, ':'); //better as array of strings 
                free(fullpath);
				return (paths);
			}
		}
		i++;
	}
	return (NULL); //need error here?
}

char *get_exec_path(char *cmd, char **path)
{
    char *tmp;
    char *commandpath; //zb /usr/bin/ls

    while (*path)
    {
        tmp = ft_strjoin(*path, "/"); //MALLOC
        commandpath = ft_strjoin(tmp, cmd); //MALLOC
        free(tmp);
        if ((access(commandpath, X_OK)) == 0)
            return (commandpath);
        free(commandpath);
        path++;
    }
    return(NULL);
}

void    exec_cmd(char *cmd, char *envp[]) //already forked, redirected in/out inherited
{
    char **path; //whole path from envp
	char *exec_path; //path that works
    char **argexe;

	argexe = ft_split(cmd, ' ');
    path = get_path(envp);   
    exec_path = get_exec_path(argexe[0], path);
    if (!exec_path)
    {
        ft_putstr_fd("no executable path\n", STDERR_FILENO);
        //FREE STUFF argexe, path, open fds
        exit(1);
    }
    free(path);
    if(execve(exec_path, argexe, envp) == -1) //??  execve closing open fds?
		exit(1); //is it freeing??
}