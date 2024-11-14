/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:59:20 by lgottsch          #+#    #+#             */
/*   Updated: 2024/11/14 17:38:12 by Watanudon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"
/*
??
when to unlink?

TO DO 
do everything new


NOTES:
stderr writes to terminal by default -> use putstr_fd for error
< is input redirection 
> output redirection, out file is created if does not already exist / overwritten if exists!
PATH holds all important paths 

simulating |  https://www.youtube.com/watch?v=6xbLgZpOBi8&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=23


./pipex file1 cmd1 cmd2 file2
*/
int check_in(char *file)
{
	int	infile;

	infile = 1;
	if (access(file, F_OK) == 0) //file 1 need to exist or read
	{
		if (access(file, R_OK) == 0)
			infile = 0;
	}
	return (infile);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	id1;
	int	id2;
	int fd[2]; //fd[0] for read out , fd[1] for write in
	
	//check arg number
	if (argc != 5)
	{
		//error
		ft_putstr_fd("args wrong, need to be 5\n", STDERR_FILENO); //CHECK ERROR IF CERTAIN ONE NEEDED
		return (0); //CHECK THIS TOO
	}
		
//check if cmds executable first??
	//check infile 
	if (check_in(argv[1]) != 0) //0 if access ok
	{
		ft_putstr_fd("infile permission denied\n", STDERR_FILENO);
		return (1);
	}

	//pipe
	if (pipe(fd) == -1)
	{
		perror("error pipe\n"); //CHECK
		return (2);
	}
	
	//fork1
	if((id1 = fork()) < 0)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO); //CHECK
		return (1);
	}
	else if (id1 == 0)  //going to execve or exit = everthing freed
		kid1(fd[0], fd[1], argv, envp);
		//dup2
		//exec //p gonna exit

	//fork2
	if ((id2 = fork()) < 0)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO); //CHECK
		return (1);
	}
	else if (id2 == 0)  //going to execve or exit = everything freed
		kid2(fd[0], fd[1], argv, envp);
		//dup2
		//exec //p gonna exit
	
	//close pipe's ends in parent
	close(fd[0]);
	close(fd[1]);
	//wait for both to finish
	wait(NULL);
	wait(NULL);
	
	return (0);
}
