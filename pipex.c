/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:59:20 by lgottsch          #+#    #+#             */
/*   Updated: 2024/11/13 17:23:59 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"
/*
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


int	main(int argc, char *argv[], char *envp[])
{
	int fd[2]; //fd[0] for read out , fd[1] for write in
	
	//check arg number
	if (argc != 5)
	{
		//error
		ft_putstr_fd("args wrong, need to be 5\n", STDERR_FILENO); //CHECK ERROR IF CERTAIN ONE NEEDED
		return (1); //CHECK THIS TOO
	}
		
	//check if cmds executable??
	//pipe
	if (pipe(fd) == -1)
	{
		perror("error pipe\n"); //CHECK
		return;
	}
	
	//fork
		//dup2
		//exec //p gonna exit
	//fork
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
