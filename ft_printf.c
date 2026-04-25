/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:16:08 by joaqumar          #+#    #+#             */
/*   Updated: 2026/04/25 14:22:25 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flush_buffer(t_printf *p)
{
	if (p->index > 0)
	{
		write(1, p->buffer, p->index);
		p->index = 0;
	}
}

void	add_to_buffer(t_printf *p, char c)
{
	if (p->index >= BUF_SIZE)
		flush_buffer(p);
	p->buffer[p->index++] = c;
	p->total_len++;
}

void	reset_flags(t_printf *p)
{
	p->dash = 0;
	p->zero = 0;
	p->dot = 0;
	p->prec = -1;
	p->width = 0;
	p->hash = 0;
	p->plus = 0;
	p->space = 0;
	p->type = 0;
}

static void	parse_format(const char *format, t_printf *p)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i = ft_parse_flags(format, i + 1, p);
			handle_conversions(p);
		}
		else
			add_to_buffer(p, format[i]);
		i++;
	}
}

int	ft_printf(const char *format, ...)
{
	t_printf	p;

	if (!format)
		return (-1);
	p.index = 0;
	p.total_len = 0;
	va_start(p.args, format);
	parse_format(format, &p);
	flush_buffer(&p);
	va_end(p.args);
	return (p.total_len);
}
