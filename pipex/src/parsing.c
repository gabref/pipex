/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 05:32:38 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/09 10:13:59 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdlib.h>

void	parse_cmds(t_pipex *p, int ac, char **av)
{
	int	i;

	i = ac - 2;
	if (p->here_doc)
		i--;
	p->cmds = malloc(sizeof(char *) * (i + 1));
	if (p->cmds == NULL)
		exit_pmessage(1, "Limit of computer memory reached");
	while (i > 1)
		p->cmds[p->cmd_count++] = ft_strdup(av[ac - i--]);
	p->cmds[p->cmd_count] = NULL;
}

void	parse_here_doc(t_pipex *p, int ac, char **av)
{
	char	*line;

	if (ac < 3 || ft_strncmp(av[1], HERE_DOC_FILE,
			ft_strlen(HERE_DOC_FILE)) != 0)
		return ;
	p->in_fd = open(HERE_DOC_FILE, O_WRONLY | O_CREAT, 0777);
	if (p->in_fd < 0)
		exit_pmessage(1, NULL);
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

int	open_file(char *pathname, t_pipex *p)
{
	if (access(pathname, F_OK))
	{
		if (p->out_fd > 0)
			write(p->out_fd, "0\n", 2);
		free_pipex(p);
		exit_message(EXIT_FAILURE, "no such file or directory\n");
	}
	if (access(pathname, R_OK))
	{
		if (p->out_fd > 0)
			write(p->out_fd, "0\n", 2);
		free_pipex(p);
		exit_message(0, "permission denied\n");
	}
	return (open(pathname, O_RDONLY));
}

t_pipex	*init_pipex(int ac, char **av)
{
	int		ofile_fd;
	t_pipex	*p;

	ofile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	p = malloc(sizeof(t_pipex));
	if (!p)
		exit(1);
	p->cmds = NULL;
	p->out_str = NULL;
	p->here_doc = FALSE;
	p->cmd_count = 0;
	p->cur_cmd_idx = -1;
	p->out_fd = ofile_fd;
	parse_here_doc(p, ac, av);
	if (p->here_doc)
		p->in_fd = open_file(HERE_DOC_FILE, p);
	else
		p->in_fd = open_file(av[1], p);
	return (p);
}
