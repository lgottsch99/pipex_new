/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:59:32 by lgottsch          #+#    #+#             */
/*   Updated: 2024/11/14 17:38:14 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The exit() function closes all open file descriptors belonging to the process and any children of the process are inherited by process 1, init, and the process parent is sent a SIGCHLD signal.



./pipex file1 cmd1 cmd2 file2

int fd[2]; //fd[0] for read out , fd[1] for write in
*/


#include "pipex.h"

void    kid1(int fd0, int fd1, char *argv[], char *envp[])
{
    int infile_fd;
	
	close(fd0); //no need to read out pipe
	
	if ((infile_fd = open(argv[1], O_RDONLY)) == -1) //open infile
	{
		ft_printf("error open infile\n"); //CHECK
		return; //???
	}
    //dup2 -> infile =input, pipe =output (fd[1] for write in)
    if ((dup2(infile_fd, STDIN_FILENO)) == -1) //redirect infile to be stdin 
	{
		ft_printf("error dup2 stdin\n"); //CHECK 
		return;
	}
    close(infile_fd);
	if ((dup2(fd1, STDOUT_FILENO)) == -1) //redirect input end of pipe to be stdout
	{
		ft_printf("error dup2 pipefile\n");
		return;
	}
	//exec //p gonna exit
    exec_cmd(argv[2], envp);//??  execve closing open fds?
}

void    kid2(int fd0, int fd1, char *argv[], char *envp[])
{
    int	outfile_fd;

	close(fd1); //no need to write in pipe
	
	//open outfile or create
	if ((outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
	{
		ft_printf("error open outfile\n"); //CHECK
		return;
	}

    //dup2 : input = fd 0 pipe (read out), output = outfile
    if((dup2(fd0, STDIN_FILENO)) == -1)
	{
		ft_printf("error dup2 stdin\n"); //CHECK
		return;
	}
	//redirect stdout to be outfile
	if((dup2(outfile_fd, STDOUT_FILENO)) == -1)
	{
		ft_printf("error dup2 stdout\n"); //CHECK
		return;
	}
	close(outfile_fd);
	exec_cmd(argv[3], envp);	//exec //p gonna exit on fail
}
