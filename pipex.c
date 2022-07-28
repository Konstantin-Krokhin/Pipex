#include "unistd.h"
#include "stdio.h"
#include "Libft/libft.h"
#include "fcntl.h" 						// ONLY FOR TESTING !
#include "TESTONLY_GNL/get_next_line.h" // ONLY FOR TESTING !

char *getting_cmd_path(char **argv, char **envp)
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
		cmd_path = ft_strjoin(paths[i], argv[2]);
		if (!(access(cmd_path, F_OK | X_OK)))
			break;
		free(cmd_path);
	}
	return(cmd_path);
}

int main (int argc, char **argv, char **envp)
{
//char *options[3] = {"ls", "-l", NULL};
//execve("/bin/ls", options, envp);

	char *cmd_path;
	
	if (!(cmd_path = getting_cmd_path(argv, envp)))
	{
		perror(cmd_path);
		return (-1);
	}
	execve(cmd_path, argv, envp);
	//printf("	cmdpath = %s\n", cmd_path);

	//execve("/bin/ls", options, envp);

	return(0);
}