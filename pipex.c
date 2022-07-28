#include "unistd.h"
#include "stdio.h"
#include "Libft/libft.h"
#include "fcntl.h" 						// ONLY FOR TESTING !
#include "TESTONLY_GNL/get_next_line.h" // ONLY FOR TESTING !

int main (int argc, char **argv, char **envp)
{
//char *options[3] = {"ls", "-l", NULL};
//execve("/bin/ls", options, envp);


	// FOR Printing with GNL
	//int fd = open("/Users/konsta/Desktop/42/Pipex/.vscode/environment_variables.txt", O_RDONLY);
	//int i = -1;
	//while (envp[++i] != NULL)
	//	envp[i] = get_next_line(fd);

	char *env_path = NULL;
	char **paths;
	char *cmd = "ls";
	int i = -1;

	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			printf("	PATHS: %s\n", env_path);
			break;
		}
	// retrieve **path variable envp and divide it with split by ':'
	paths = ft_split(env_path, ':');

	i = -1;
	char *tmp;
	// add '/' sign with strjoin to each path element
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	
	i = -1;
	char *cmd_path;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!(access(cmd_path, F_OK | X_OK)))
			break;
		free(cmd_path);
	}
	
	printf("	cmdpath = %s\n", cmd_path);

	//execve("/bin/ls", options, envp);

	return(0);
}