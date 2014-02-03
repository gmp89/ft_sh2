/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 15:50:35 by gpetrov           #+#    #+#             */
/*   Updated: 2014/02/03 15:37:53 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_setenv(t_data *data, char *str)
{
	int		j;
	int		i;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = data->env;
	while (data->env[j] != 0)
		j++;
	data->env = (char **)malloc(sizeof(char *) * (j + 2));
	while (tmp[i] != 0)
	{
		data->env[i] = ft_strdup(tmp[i]);
		i++;
	}
	data->env[i] = ft_strdup(str);
	data->env[i + 1] = 0;
}

int		ft_checkenv(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (data->env[i] != 0)
	{
		if (ft_strcmp(data->env[i], str) == 0)
			return (1);
		i++;
	}
	ft_putstr("[ENV] - Not Found.\n");
	return (0);
}

int		ft_unsetenv(t_data *data, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = data->env;
	if (ft_checkenv(data, str) == 0)
		return (0);
	while (data->env[i] != 0)
	{
		if (ft_strcmp(data->env[i], str) == 0)
		{
			while (tmp[i] != 0)
			{
				if (tmp[i + 1])
					data->env[i] = ft_strdup(tmp[i + 1]);
				else
					data->env[i] = 0;
				i++;
			}
			break ;
		}
		i++;
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_data		data;
	char		*tmp;

	(void)ac;
	(void)av;
	tmp = NULL;
	data.env = env;
	data.old_pwd = getcwd(tmp, 4096);
	ft_set_prompt(&data);
	while (42)
	{
		ft_get_pwd(&data, env);
		ft_putstr(data.pwd + 43);
		ft_putstr(" $> ");
		if (ft_get_cmd(&data) == 0)
		{
			if (ft_exec_cmd(&data) == 0)
				free(data.name_cmd);
		}
	}
	return (0);
}

int		ft_exec(t_data *data)
{
	char	*tmp;
	char	**path;
	int		i;
	int		t;

	path = ft_get_path(data->env);
	i = 0;
	while (path[i] != 0)
	{
		tmp = ft_strjoin(path[i], data->name_cmd);
		t = access(tmp, X_OK);
		execve(tmp, data->argv, data->env);
		free(tmp);
		i++;
	}
	execve(data->name_cmd, data->argv, data->env);
	if (t == -1 && ft_strcmp(data->name_cmd, "exit") != 0)
		ft_cmd_error();
	return (0);
}

int		ft_exec_cmd(t_data *data)
{
	int		ret;

	if (ft_strcmp(data->name_cmd, "setenv") == 0)
		ft_setenv(data, data->argv[1]);
	if (ft_strcmp(data->name_cmd, "unsetenv") == 0)
		ft_unsetenv(data, data->argv[1]);
	if (ft_strcmp(data->name_cmd, "cd") == 0)
		ft_cd_help(data);
	data->pid = fork();
	if (data->pid == -1)
		print_pid_error();
	if (data->pid == 0 && ft_strcmp(data->name_cmd, "cd") != 0
	 && ft_strcmp(data->name_cmd, "setenv") != 0 &&
	 ft_strcmp(data->name_cmd, "unsetenv") != 0)
	{
		ft_exec(data);
		exit(0);
	}
	if (data->pid > 0)
		wait(&ret);
	return (0);
}
