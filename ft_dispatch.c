/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:17:19 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/05 17:34:57 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_percent(t_printf *p)
{
	add_to_buffer(p, '%');
}

void	handle_char(t_printf *p)
{
	char	c;

	c = (char)va_arg(p->args, int);
	if (!p->dash)
		ft_print_padding(p, p->width - 1, ' ');
	add_to_buffer(p, c);
	if (p->dash)
		ft_print_padding(p, p->width - 1, ' ');
}

void	handle_conversions(t_printf *p)
{
	if (p->type == 'c')
		handle_char(p);
	else if (p->type == 's')
		handle_string(p);
	else if (p->type == 'p')
		handle_pointer(p);
	else if (p->type == 'd' || p->type == 'i')
		handle_int(p);
	else if (p->type == 'u')
		handle_unsigned(p);
	else if (p->type == 'x' || p->type == 'X')
		handle_hex(p);
	else if (p->type == '%')
		handle_percent(p);
}
