/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 15:50:35 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/31 15:50:14 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_get_pwd(t_data *data, char **env)
{
	char		*tmp;

	tmp = NULL;
	(void)env;
	data->pwd = getcwd(tmp, 256);
	free(tmp);
}

void	ft_set_prompt(t_data *data)
{
	char		*user;

	data->prompt = ft_strnew(1);
	user = ft_get_user(data->env, data);
	ft_putstr("$> Welcome ");
	ft_putstr(user);
	ft_putstr("\n");
}

int		main(int ac, char **av, char **env)
{
	t_data		data;
	char		*tmp;

	ac = 0;
	av = 0;
	tmp = NULL;
	data.env = env;
	data.old_pwd = getcwd(tmp, 256);
	ft_set_prompt(&data);
	while (42)
	{
		ft_get_pwd(&data, env);
		ft_putstr(data.pwd + 43);
		ft_putstr(" $> ");
		if (ft_get_cmd(&data) == 0)
		{
			ft_exec_cmd(&data);
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
		if (data->prompt[0] == '/')
		data->name_cmd = ft_direct_exec(data);
		tmp = ft_strjoin(path[i], data->name_cmd);
		t = access(tmp, X_OK);
		execve(tmp, data->argv, data->env);
		free(tmp);
		i++;
	}
	if (t == -1 && ft_strcmp(data->name_cmd, "exit") != 0)
	{
		ft_putstr("[NOT_FOUND] : cherche pas la petite bete.");
		ft_putchar('\n');
		exit(0);
	}
	return (0);
}

void	ft_cd_help(t_data *data)
{

	data->old_pwd = data->pwd;
	if (!data->argv[1])
		chdir(data->home);
	else if (ft_strcmp(data->argv[1], "~") == 0)
		chdir(data->home);
	else if (ft_strcmp(data->argv[1], "-") == 0)
		chdir(data->old_pwd);
	else
		chdir(data->argv[1]);
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
