/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agertha <agertha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:18:54 by lalex             #+#    #+#             */
/*   Updated: 2022/10/17 13:42:27 by agertha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_com_new1(t_com	*com, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	com->arg = malloc(sizeof(char *) * i + 1);
	if (!com->arg)
		return ;
	com->arg[i] = NULL;
	i = -1;
	while (arr[++i])
		com->arg[i] = ft_substr(arr[i], 0, ft_strlen(arr[i]));
}

int	make_arg(char ***arg, char **arr, int i)
{
	int		n;
	int		j;

	j = 0;
	n = ft_n_words(arr, i);
	if (n == 0)
	{
		*arg = NULL;
		return (0);
	}
	*arg = malloc(sizeof(char *) * (n + 1));
	while (j < n)
	{
		(*arg)[j++] = ft_substr(arr[i], 0, ft_strlen(arr[i]));
		i++;
	}
	(*arg)[j] = NULL;
	return (n);
}

t_com	*com_new1(char *name, char **arr, int delim, char *file)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	if (!com)
		return (NULL);
	com->name = ft_substr(name, 0, ft_strlen(name));
	ft_free(name);
	if (arr)
	{
		fill_com_new1(com, arr);
		free_array(arr);
	}
	else
		com->arg = NULL;
	com->delim = delim;
	com->file = ft_substr(file, 0, ft_strlen(file));
	com->next = NULL;
	return (com);
}

int	make_new_com(int i, char **arr, t_com **new_com)
{
	char	*name;
	char	**arg;

	name = ft_substr(arr[i], 0, ft_strlen(arr[i]));
	i++;
	i = i + make_arg(&arg, arr, i);
	if (arr[i] && delimetr(arr[i]) > 1)
	{
		*new_com = com_new1(name, arg, delimetr(arr[i]), arr[i + 1]);
		i = i + 2;
	}
	else if (arr[i] && delimetr(arr[i]) == 1)
	{
		i++;
		*new_com = com_new1(name, arg, 1, 0);
	}
	else
		*new_com = com_new1(name, arg, 0, 0);
	return (i);
}

void	make_struct(char **arr, t_com **com)
{
	t_com	*new_com;
	t_com	*tmp;
	int		i;

	new_com = NULL;
	*com = init_com();
	tmp = *com;
	i = 0;
	while (arr[i])
	{
		make_struct1(arr, &i, &new_com);
		com_add_back(com, new_com);
	}
	*com = (*com)->next;
	ft_one_name(com);
	free(tmp);
}
