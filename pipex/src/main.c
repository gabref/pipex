#include "../inc/pipex.h"

void	free_pipex(t_pipex *p);

void	free_2d_array(void **arr_arr)
{
	int	i;

	i = 0;
	while (arr_arr && arr_arr[i])
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

// 	0      1      2  3   4    5   6
// ./pipex infile ls cat grep pwd out
// ac = 7
// ac - 2 = 5 = i
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
	if (p->here_doc)
		i--;
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

	close(p->pfd[0]);
	dup2(p->pfd[1], STDOUT_FILENO);
	close(p->pfd[1]);
	args = ft_split(cmd, ' ');
	cmd_path = get_path_for_executable(cmd, env);
	if (cmd_path == NULL)
	{
		free(args);
		exit(127);
	}
	execve(cmd_path, args, env);
}

void	exec(t_pipex *p, char **env)
{
	pid_t	child_pid;
	int		status;

	dup2(p->in_fd, STDIN_FILENO);
	while (++(p->cur_cmd_idx) < p->cmd_count)
	{
		pipe(p->pfd);
		child_pid = fork();
		if (child_pid < 0)
		{
			free_pipex(p);
			perror("Error while forking");
			exit(1);
		}
		else if (child_pid == 0)
		{
			exec_comand(p->cmds[p->cur_cmd_idx], env, p);
		}
		else
		{
			close(p->pfd[1]);
			dup2(p->pfd[0], STDIN_FILENO);
			if (waitpid(child_pid, &status, 0) < 0)
			{
				free_pipex(p);
				perror("waitpid() failed");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) != 0)
				{
					if (WEXITSTATUS(status) == 127)
						printf("command not found: %s\n", p->cmds[p->cur_cmd_idx]);
					else
						printf("%s\n", strerror(WEXITSTATUS(status)));
					free_pipex(p);
					exit(WEXITSTATUS(status));
				}
			}
		}
	}
	p->out_str = read_file_to_string(p->pfd[0]);
	close(p->pfd[1]);
	if (p->out_str)
		write(p->out_fd, p->out_str, ft_strlen(p->out_str));
}

void	parse_here_doc(t_pipex *p, int ac, char **av)
{
	char	*line;

	if (ac < 3 || ft_strncmp(av[1], "here_doc", 8) != 0)
		return ;
	p->in_fd = open("here_doc", O_WRONLY | O_CREAT, 0777);
	if (p->in_fd < 0)
	{
		perror(0);
		exit(1);
	}
	p->here_doc = TRUE;
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(av[2], line, ft_strlen(line) - 1) == 0)
		{
			free(line);
			return ;
		}
		write(p->in_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(p->in_fd);
}

t_pipex	*init_pipex(int ac, char **av)
{
	int		ofile_fd;
	t_pipex	*p;

	ofile_fd = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	p = malloc(sizeof(t_pipex));
	if (!p)
		exit(1);
	p->out_str = NULL;
	p->here_doc = FALSE;
	p->cmd_count = 0;
	p->cur_cmd_idx = -1;
	p->out_fd = ofile_fd;
	parse_here_doc(p, ac, av);
	if (p->here_doc)
		p->in_fd = open("here_doc", O_RDONLY);
	else
		p->in_fd = open(av[1], O_RDONLY);
	if (p->in_fd < 0)
	{
		perror(0);
		exit(1);
	}
	return (p);
}

void	free_pipex(t_pipex *p)
{
	close(p->in_fd);
	close(p->out_fd);
	if (p->out_str)
		free(p->out_str);
	if (p->here_doc)
		unlink("here_doc");
	free_2d_array((void **)p->cmds);
	free(p);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*p;

	if (ac < 4)
		return (0);
	p = init_pipex(ac, av);
	parse_cmds(p, ac, av);
	exec(p, env);
	free_pipex(p);
	return (0);
}
