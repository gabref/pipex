#include "../inc/pipex.h"

char *get_path()
{
	
}

void	exec_comand(char *cmd, char **env, t_pipex *p)
{
	// in child
	(void)cmd;
	(void)env;
	(void)p;
	// child
	close(p->pfd[0]);
	dup2(p->pfd[1], STDOUT_FILENO);
	close(p->pfd[1]);
	char *const args[] = {"ls",  NULL};
	execve("/bin/ls", args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void exec(t_pipex *p, char **env)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Error while forking");
		exit(1);
	}
	else if (child_pid == 0)
	{
		exec_comand("", env, p);
	}
	else
	{
		// parent
		printf("parent %d, waiting for %d to finish\n", getpid(), child_pid);
		close(p->pfd[1]);
		waitpid(child_pid, NULL, 0);
		p->out_str = read_file_to_string(p->pfd[0]);
		close(p->pfd[0]);
	}
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
	return (p);
}

void	free_pipex(t_pipex *p)
{
	close(p->in_fd);
	close(p->out_fd);
	free(p->in_str);
	free(p->out_str);
	free(p);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*p;

	(void)env;
	if (ac < 4)
		return (0);
	p = init_pipex(ac, av);
	p->in_str = read_file_to_string(p->in_fd);
	pipe(p->pfd);

	exec(p, env);

	free_pipex(p);
	return (0);
}
