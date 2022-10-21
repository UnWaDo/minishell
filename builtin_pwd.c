/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agertha <agertha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:53:59 by lalex             #+#    #+#             */
/*   Updated: 2022/10/17 13:51:32 by agertha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_envp *envp_list)
{
	char	*pwd;

	if (!envp_list)
		return (1);
	pwd = get_value_from_envp(envp_list, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			if (chdir("..") == -1)
			{
				perror("Myshell 🐚: pwd: ");
				return (1);
			}
			pwd = getcwd(NULL, 0);
		}
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
