#include "../inc/pipex.h"
#include <unistd.h>

void	free_2d_array(void **arr_arr)
{
	int	i;

	i = 0;
	while (arr_arr[i])
		free(arr_arr[i++]);
	free(arr_arr);
}

char	*get_env(char *var, char **env)
{
	int		i;
	char	**split_env;
	char	*env_name;
	char	*env_contents;

	i = 0;
	while (env[i])
	{
		split_env = ft_split(env[i++], '=');
		env_name = split_env[0];
		if (ft_strncmp(env_name, var, ft_strlen(env_name)) == 0)
		{
			env_contents = ft_strdup(split_env[1]);
			free_2d_array((void **)split_env);
			return (env_contents);
		}
		free_2d_array((void **)split_env);
	}
	return (NULL);
}

char	*get_path_for_executable(char *cmd, char **env)
{
	char	*path_str;
	char	**paths;
	int		i;
	char	*path;
	char	*cmd_path;
	char	**cmd_args;
	char	*cmd_to_execute;

	path_str = get_env("PATH", env);
	paths = ft_split(path_str, ':');
	cmd_args = ft_split(cmd, ' ');
	cmd_to_execute = ft_strdup(cmd_args[0]);
	free_2d_array((void **)cmd_args);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		cmd_path = ft_strjoin(path, cmd_to_execute);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(path);
			free(path_str);
			free(cmd_to_execute);
			free_2d_array((void **)paths);
			return (cmd_path);
		}
		free(path);
		free(cmd_path);
	}
	free_2d_array((void **)paths);
	free(cmd_to_execute);
	free(path_str);
	return (NULL);
}

// 	0      1      2  3   4
// ./pipex infile ls cat out
// ac = 5
// ac - 2 = 3 = i
// ac - i = 2

//  0      1      2
// ./pipex infile out
// ac = 3
// ac - 2 = 1 = i
// ac - i = 2

void	parse_cmds(t_pipex *p, int ac, char **av)
{
	int	i;

	i = ac - 2;
	p->cmds = malloc(sizeof(char *) * (i + 1));
	if (p->cmds == NULL)
	{
		perror("Limit of computer memory reached");
		exit(1);
	}
	while (i > 1)
		p->cmds[p->cmd_count++] = ft_strdup(av[ac - i--]);
	p->cmds[p->cmd_count] = NULL;
}

void	exec_comand(char *cmd, char **env, t_pipex *p)
{
	char	**args;
	char	*cmd_path;

	printf("CHILD: %d, it: %d, about to configure the dup2 stuff\n", getpid(),
		p->cur_cmd_idx);
	close(p->pfd[0]);
	dup2(p->pfd[1], STDOUT_FILENO);
	close(p->pfd[1]);
	args = ft_split(cmd, ' ');
	cmd_path = get_path_for_executable(cmd, env);
	execve(cmd_path, args, NULL);
	perror("command not found");
	exit(EXIT_FAILURE);
}

void	exec(t_pipex *p, char **env)
{
	pid_t	child_pid;

	dup2(p->in_fd, STDIN_FILENO);
	while (++(p->cur_cmd_idx) < p->cmd_count)
	{
		pipe(p->pfd);
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("Error while forking");
			exit(1);
		}
		else if (child_pid == 0)
			exec_comand(p->cmds[p->cur_cmd_idx], env, p);
		else
		{
			close(p->pfd[1]);
			dup2(p->pfd[0], STDIN_FILENO);
			waitpid(child_pid, NULL, 0);
			printf("child finished\n\n");
		}
	}
	p->out_str = read_file_to_string(p->pfd[0]);
	close(p->pfd[0]);
	if (p->out_str)
		write(p->out_fd, p->out_str, ft_strlen(p->out_str));
}

t_pipex	*init_pipex(int ac, char **av)
{
	int		ifile_fd;
	int		ofile_fd;
	t_pipex	*p;

	ifile_fd = open(av[1], O_RDONLY);
	if (ifile_fd < 0)
	{
		perror(0);
		exit(1);
	}
	ofile_fd = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	p = malloc(sizeof(t_pipex));
	if (!p)
	{
		exit(1);
	}
	p->in_fd = ifile_fd;
	p->out_fd = ofile_fd;
	p->in_str = NULL;
	p->out_str = NULL;
	p->cmd_count = 0;
	p->cur_cmd_idx = -1;
	return (p);
}

void	free_pipex(t_pipex *p)
{
	close(p->in_fd);
	close(p->out_fd);
	free(p->in_str);
	free(p->out_str);
	if (p->cmd_count > 0)
		free_2d_array((void **)p->cmds);
	free(p);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*p;

	if (ac < 4)
		return (0);
	p = init_pipex(ac, av);
	// parse_args();
	parse_cmds(p, ac, av);
	exec(p, env);
	free_pipex(p);
	return (0);
}
