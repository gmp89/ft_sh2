/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 14:22:26 by gpetrov           #+#    #+#             */
/*   Updated: 2014/02/03 15:23:12 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_pid_error(void)
{
	ft_putstr("fork : problem.");
	ft_putchar('\n');
}

void	ft_cmd_error(void)
{
	ft_putstr("[NOT_FOUND] : cherche pas la petite bete.");
	ft_putchar('\n');
	exit(0);
}

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

void	ft_cd_help(t_data *data)
{
	if (!data->argv[1])
		chdir(data->home);
	else if (ft_strcmp(data->argv[1], "~") == 0)
		chdir(data->home);
	else if (ft_strcmp(data->argv[1], "-") == 0)
		chdir(data->old_pwd);
	else
		chdir(data->argv[1]);
	data->old_pwd = data->pwd;
}

void	ft_print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		ft_putstr(tab[i]);
		ft_putchar('\n');
		i++;
	}
}
