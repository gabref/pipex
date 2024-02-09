/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 05:29:34 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/09 06:31:50 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exit_message(int exit_code, char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(exit_code);
}

void	exit_pmessage(int exit_code, char *msg)
{
	perror(msg);
	exit(exit_code);
}

void	free_pipex(t_pipex *p)
{
	if (p->in_fd > 0)
		close(p->in_fd);
	if (p->out_fd > 0)
		close(p->out_fd);
	if (p->out_str)
		free(p->out_str);
	if (p->here_doc)
		unlink(HERE_DOC_FILE);
	free_2d_array((void **)p->cmds);
	free(p);
}

void	free_2d_array(void **arr_arr)
{
	int	i;

	i = 0;
	while (arr_arr && arr_arr[i])
		free(arr_arr[i++]);
	free(arr_arr);
}
