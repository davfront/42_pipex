/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_parse_cmd_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:00:37 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/22 13:05:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_update_quote(char *quote, char const *prev, char const *curr)
{
	if (!*quote)
	{
		if (*curr == '"' || *curr == '\'')
			*quote = *curr;
	}
	else if (*curr == *quote && *prev != '\\')
		*quote = '\0';
}

size_t	pip_count_cmd_args(char const *s)
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
			n++;
		pip_update_quote(&quote, &s[i - 1], &s[i]);
		i++;
	}
	return (n);
}

static char	*pip_copy_cmd_arg(char const *s, size_t idx[3])
{
	char	*str;
	size_t	i;
	size_t	j;
	char	quote;

	str = malloc((idx[1] - idx[0] - idx[2] + 2) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	i = 0;
	quote = '\0';
	while (i <= idx[1])
	{
		if (s[i] == quote && s[i - 1] == '\\')
			j--;
		if (i >= idx[0])
			str[j] = s[i];
		pip_update_quote(&quote, &s[i - 1], &s[i]);
		if (i >= idx[0])
			j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*pip_get_cmd_arg(char const *s)
{
	size_t	len;
	size_t	i;
	char	quote;
	size_t	idx[3];

	len = 0;
	i = 0;
	quote = '\0';
	idx[2] = 0;
	while (s[i] && (s[i] != ' ' || quote))
	{
		if (quote && s[i] == quote && s[i - 1] == '\\')
			idx[2]++;
		pip_update_quote(&quote, &s[i - 1], &s[i]);
		i++;
	}
	len = i;
	idx[0] = (s[0] == '"' || s[0] == '\'');
	idx[1] = len - 1;
	if (idx[0] == 1 && idx[1] > 0 && s[idx[1]] == s[0])
		idx[1]--;
	return (pip_copy_cmd_arg(s, idx));
}
