/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 15:50:35 by gpetrov           #+#    #+#             */
/*   Updated: 2014/02/03 13:34:18 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

	if (ft_strcmp(data->name_cmd, "cd") == 0)
		ft_cd_help(data);
	data->pid = fork();
	if (data->pid == -1)
		print_pid_error();
	if (data->pid == 0 && ft_strcmp(data->name_cmd, "cd") != 0)
	{
		ft_exec(data);
		exit(0);
	}
	if (data->pid > 0)
		wait(&ret);
	return (0);
}
