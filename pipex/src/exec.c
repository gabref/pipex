/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 05:36:19 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/09 06:22:36 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
		free_pipex(p);
		free_2d_array((void **) args);
		exit(127);
	}
	execve(cmd_path, args, env);
}

void	exec_parent(t_pipex *p, int child_pid)
{
	int	status;

	close(p->pfd[1]);
	dup2(p->pfd[0], STDIN_FILENO);
	if (waitpid(child_pid, &status, 0) < 0)
	{
		free_pipex(p);
		exit_pmessage(EXIT_FAILURE, "waitpid() failed");
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
			free_pipex(p);
			exit_pmessage(1, "Error while forking");
		}
		else if (child_pid == 0)
			exec_comand(p->cmds[p->cur_cmd_idx], env, p);
		else
			exec_parent(p, child_pid);
	}
	p->out_str = read_file_to_string(p->pfd[0]);
	close(p->pfd[1]);
	if (p->out_str)
		write(p->out_fd, p->out_str, ft_strlen(p->out_str));
}
