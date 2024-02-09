/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 05:36:45 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/09 08:25:20 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	*p;

	if (ac < 3)
		return (128);
	p = init_pipex(ac, av);
	parse_cmds(p, ac, av);
	exec(p, env);
	free_pipex(p);
	return (0);
}
