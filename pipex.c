#include "unistd.h"
#include "stdio.h"
#include "Libft/libft.h"
#include "Libft/ft_printf.h"
#include "fcntl.h"

char *getting_cmd_path(char *argv, char **envp)
{
	// --- PARSING ENVIRONMENTAL VARIABLES
	char *env_path = NULL;
	char **paths;
	int i = -1;

	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break;
		}
	// retrieve **path variable envp and divide it with split by ':'
	paths = ft_split(env_path, ':');

	// -------- ADDING / to end of each path to check them later
	i = -1;
	char *tmp;
	// add '/' sign with strjoin to each path element
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	
	// -------- CHECKING ACCESS ---------

	i = -1;
	char *cmd_path;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], argv);
		if (!(access(cmd_path, F_OK | X_OK)))
			break;
		free(cmd_path);
	}
	return(cmd_path);
}

void do_child_work(char **argv, char **envp, int pipe_ends[2], int out_fd, int i)
{
	char *cmd_path;
	
	dup2(out_fd, STDOUT_FILENO);
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	char **cmd = ft_split(argv[i + 2], ' ');
	if (!(cmd_path = getting_cmd_path(cmd[0], envp)))
		perror(cmd_path);
	execve(cmd_path, cmd, envp);
}

int main (int argc, char **argv, char **envp)
{
	int pipe_ends[2];
	
	if (argc < 3)
		return (1);

	pid_t pid;

	int i = 0;
	int in_file = open(argv[1], O_RDONLY);
	int out_file = open(argv[argc - 1], O_RDWR | O_CREAT \
														| O_TRUNC, 0666);

	if (in_file == -1)
		write(1, "Open infile failed", 40);
	if (out_file == -1)
		write(1, "Open outfile failed", 50);
	
	dup2(in_file, STDIN_FILENO);

	while (i < argc - 3)
	{
		if (pipe(pipe_ends) == -1)
			return(1);
		
		if ((pid = fork()) == -1)
			return (1);
		else if (pid == 0)
		{
			int size = 0;
			while (argv[size] != 0)
				size++;
			if (i == size - 4)
				do_child_work(argv, envp, pipe_ends, out_file, i);
			else
				do_child_work(argv, envp, pipe_ends, pipe_ends[1], i);
		}
		waitpid(pid, NULL, 0);
		dup2(pipe_ends[0], STDIN_FILENO);
		close(pipe_ends[0]);
		close(pipe_ends[1]);
		i++;
	}
	close(in_file);
	close(out_file);

	return(0);
}