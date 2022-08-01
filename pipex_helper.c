/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokrokhi <kokrokhi@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:17:35 by kokrokhi          #+#    #+#             */
/*   Updated: 2022/08/02 00:19:22 by kokrokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp, int i)
{
	char	*env_path;

	env_path = NULL;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break ;
		}
	}
	return (env_path);
}

char	*getting_cmd_path(char *argv, char **envp)
{
	char	*env_path;
	char	*cmd_path;
	char	**paths;
	char	*tmp;
	int		i;

	env_path = find_path(envp, -1);
	paths = ft_split(env_path, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], argv);
		if (!(access(cmd_path, F_OK | X_OK)))
			break ;
		free (cmd_path);
	}
	return (cmd_path);
}

void	do_child_work(char *argv, char **envp,
						int pipe_ends[2], int out_fd)
{
	char	*cmd_path;
	char	**cmd;

	dup2(out_fd, STDOUT_FILENO);
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	cmd = ft_split(argv, ' ');
	cmd_path = getting_cmd_path(cmd[0], envp);
	if (!cmd_path)
		perror(cmd_path);
	if (!execve(cmd_path, cmd, envp))
		write(3, "!", 1);
}

void	open_files(int argc, char **argv, int *in_file, int *out_file)
{
	*in_file = open(argv[1], O_RDONLY);
	*out_file = open(argv[argc - 1], O_RDWR | O_CREAT \
														| O_TRUNC, 0666);
	if (*in_file == -1)
		write(1, "Opening infile failed!\n", 26);
	if (*out_file == -1)
		write(1, "Opening outfile failed!\n", 27);
	dup2(*in_file, STDIN_FILENO);
}
