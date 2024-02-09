/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:55:45 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/09 05:17:44 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/gnl/get_next_line_bonus.h"
# include "../libs/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# define PATH "PATH"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}			t_bool;

typedef struct s_pipex
{
	int		in_fd;
	int		pfd[2];
	int		out_fd;
	t_bool	here_doc;
	int		cmd_count;
	int		cur_cmd_idx;
	char	*in_str;
	char	*out_str;
	char	**cmds;
	t_bool	is_invalid_infile;
}			t_pipex;

char		*read_file_to_string(int fd);

#endif
