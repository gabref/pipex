/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 05:34:52 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/09 08:13:05 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

char	**get_paths_of_path_env(char **env)
{
	char	*path_str;
	char	**paths;

	path_str = get_env("PATH", env);
	paths = ft_split(path_str, ':');
	free(path_str);
	return (paths);
}

char	*get_command(char *cmd)
{
	char	**cmd_args;
	char	*cmd_to_execute;

	cmd_args = ft_split(cmd, ' ');
	cmd_to_execute = ft_strdup(cmd_args[0]);
	free_2d_array((void **)cmd_args);
	return (cmd_to_execute);
}

char	*get_path_for_executable(char *cmd, char **env)
{
	char	**paths;
	int		i;
	char	*path;
	char	*cmd_path;
	char	*cmd_to_execute;

	paths = get_paths_of_path_env(env);
	cmd_to_execute = get_command(cmd);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		cmd_path = ft_strjoin(path, cmd_to_execute);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		free(path);
		free(cmd_path);
		cmd_path = NULL;
	}
	free(cmd_to_execute);
	free_2d_array((void **)paths);
	return (cmd_path);
}
