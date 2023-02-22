/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_parse_cmd_args_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:00:37 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/22 13:06:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	pip_set_cmd_args(char **args, char const *s)
{
	size_t	n;
	size_t	i;
	char	quote;

	n = 0;
	i = 0;
	quote = '\0';
	while (s[i])
	{
		if (!quote && s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
		{
			args[n] = pip_get_cmd_arg(s + i);
			if (!args[n])
			{
				ft_free_split(args);
				return (0);
			}
			n++;
		}
		pip_update_quote(&quote, &s[i - 1], &s[i]);
		i++;
	}
	args[n] = NULL;
	return (1);
}

char	**pip_parse_cmd_args(char const *s)
{
	char	**args;
	size_t	len;

	if (!s)
		return (NULL);
	len = pip_count_cmd_args(s);
	args = (char **)malloc((len + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	if (!pip_set_cmd_args(args, s))
		return (NULL);
	return (args);
}
