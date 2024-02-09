/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:55:45 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/09 06:31:11 by galves-f         ###   ########.fr       */
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
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define PATH "PATH"
# define HERE_DOC_FILE "here_doc"

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

void		free_2d_array(void **arr_arr);
void		free_pipex(t_pipex *p);
void		exit_pmessage(int exit_code, char *msg);
void		exit_message(int exit_code, char *msg);
char		*read_file_to_string(int fd);
void		parse_here_doc(t_pipex *p, int ac, char **av);
void		parse_cmds(t_pipex *p, int ac, char **av);
char		*get_path_for_executable(char *cmd, char **env);
char		*get_env(char *var, char **env);
void		exec(t_pipex *p, char **env);
t_pipex		*init_pipex(int ac, char **av);

#endif
