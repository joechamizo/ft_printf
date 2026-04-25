/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:16:42 by joaqumar          #+#    #+#             */
/*   Updated: 2026/04/25 14:19:40 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi_simple(const char *str, int *i)
{
	int	res;

	res = 0;
	while (ft_isdigit(str[*i]))
	{
		res = (res * 10) + (str[*i] - '0');
		(*i)++;
	}
	return (res);
}

static int	is_flag_char(char c)
{
	return (c == '-' || c == '0' || c == '#' || c == '+' || c == ' ');
}

int	ft_parse_flags(const char *str, int i, t_printf *p)
{
	reset_flags(p);
	while (str[i] && is_flag_char(str[i]))
	{
		if (str[i] == '-')
			p->dash = 1;
		if (str[i] == '0' && !p->dash)
			p->zero = 1;
		if (str[i] == '#')
			p->hash = 1;
		if (str[i] == '+')
			p->plus = 1;
		if (str[i] == ' ')
			p->space = 1;
		i++;
	}
	if (ft_isdigit(str[i]))
		p->width = ft_atoi_simple(str, &i);
	if (str[i] == '.')
	{
		p->dot = 1;
		i++;
		p->prec = ft_atoi_simple(str, &i);
	}
	p->type = str[i];
	return (i);
}
