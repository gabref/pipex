/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:07:57 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/07 18:35:39 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*read_file_to_string(int fd)
{
	char	*file_as_string;
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	file_as_string = ft_strdup("");
	while (line != NULL)
	{
		tmp = file_as_string;
		file_as_string = ft_strjoin(tmp, line);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	return (file_as_string);
}
