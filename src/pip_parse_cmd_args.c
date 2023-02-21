/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_parse_cmd_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:00:37 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/21 15:58:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	pip_count_cmd_args(char const *s)
{
	size_t	n;
	size_t	i;
	char	quote;

	n = 0;
	i = 0;
	quote = '\0';
	while (s[i])
	{
		if (!quote)
		{
			if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
				n++;
			if ((s[i] == '"' || s[i] == '\''))
				quote = s[i];
		}
		else if (s[i] == quote)
			quote = '\0';
		i++;
	}
	return (n);
}

static char	*pip_get_cmd_arg(char const *s)
{
	char	*str;
	int		len;
	int		i;
	int		j;
	char	quote;
	int		start;
	int		end;
	int		escapes;

	len = 0;
	i = 0;
	quote = '\0';
	escapes = 0;
	while (s[i] && (s[i] != ' ' || quote))
	{
		if (!quote)
		{
			if ((s[i] == '"' || s[i] == '\''))
				quote = s[i];
		}
		else if (s[i] == quote)
		{
			if (s[i - 1] != '\\')
				quote = '\0';
			else
				escapes++;
		}
		i++;
	}
	len = i;
	start = 0;
	end = len - 1;
	if (s[0] == '"' || s[0] == '\'')
	{
		start++;
		if (end > 0 && s[end] == s[0])
			end--;
	}
	str = (char *)malloc((end - start - escapes + 2) * sizeof(char));
	if (!str)
		return (NULL);
	j = -1 * start;
	i = 0;
	quote = '\0';
	while (i <= end)
	{
		if (s[i] == quote && s[i - 1] == '\\')
			j--;
		if (j >= 0)
			str[j] = s[i];
		if (!quote)
		{
			if ((s[i] == '"' || s[i] == '\''))
				quote = s[i];
		}
		else if (s[i] == quote && s[i - 1] != '\\')
			quote = '\0';
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	pip_free_cmd_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

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
		if (!quote)
		{
			if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
			{
				args[n] = pip_get_cmd_arg(s + i);
				if (!args[n])
				{
					pip_free_cmd_args(args);
					return (0);
				}
				n++;
			}
			if ((s[i] == '"' || s[i] == '\''))
				quote = s[i];
		}
		else if (s[i] == quote && s[i - 1] != '\\')
			quote = '\0';
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
