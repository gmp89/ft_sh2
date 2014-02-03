/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 15:49:20 by gpetrov           #+#    #+#             */
/*   Updated: 2014/02/03 12:55:18 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"

/*
** Struct
*/

typedef struct	s_data
{
	int			pid;
	char		*name_cmd;
	char		**env;
	char		*prompt;
	char		**argv;
	char		*home;
	char		*path;
	char		*dir_cmd;
	char		*pwd;
	char		*old_pwd;
}				t_data;

/*
** Prototypes
*/

int		ft_get_cmd(t_data *data);
char	*ft_get_user(char **tab, t_data *data);
int		ft_count_c(char *str, char c);
char	**ft_get_path(char **tab);
int		ft_exec(t_data *data);
int		ft_exec_cmd(t_data *data);
char	*ft_direct_exec(t_data *data);
void	ft_get_pwd(t_data *data, char **env);
void	ft_cd_help(t_data *data);
void	print_pid_error(void);
void	ft_cmd_error(void);
void	ft_set_prompt(t_data *data);

#endif
