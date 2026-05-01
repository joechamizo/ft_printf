/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:27:31 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/01 22:13:48 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_hex_prefix(t_printf *p, unsigned long n)
{
	if (p->type == 'p')
		ft_putstr_buffer(p, "0x", 2);
	else if (p->hash && n != 0)
	{
		if (p->type == 'x')
			ft_putstr_buffer(p, "0x", 2);
		else if (p->type == 'X')
			ft_putstr_buffer(p, "0X", 2);
	}
}

static void	print_hex_number(t_printf *p, unsigned int n)
{
	if (p->type == 'x')
		ft_putnbr_base_buffer(p, n, "0123456789abcdef");
	else
		ft_putnbr_base_buffer(p, n, "0123456789ABCDEF");
}

void	handle_hex(t_printf *p)
{
	unsigned int	n;
	int				len;
	int				z;
	int				w;

	n = va_arg(p->args, unsigned int);
	len = ft_get_num_len(n, 16);
	if (n == 0 && p->dot && p->prec == 0)
		len = 0;
	z = 0;
	if (p->prec > len)
		z = p->prec - len;
	w = p->width - (z + len);
	if (p->hash && n != 0)
		w -= 2;
	if (!p->dash && (!p->zero || (p->dot && p->prec >= 0)))
		ft_print_padding(p, w, ' ');
	print_hex_prefix(p, n);
	if (!p->dash && p->zero && (!p->dot || p->prec < 0))
		ft_print_padding(p, w, '0');
	ft_print_padding(p, z, '0');
	if (len > 0)
		print_hex_number(p, n);
	if (p->dash)
		ft_print_padding(p, w, ' ');
}

void	handle_pointer(t_printf *p)
{
	unsigned long	ptr;
	int				len;
	int				w;

	ptr = (unsigned long)va_arg(p->args, void *);
	len = ft_get_num_len(ptr, 16);
	if (!ptr)
		len = 5;
	w = p->width - len;
	if (ptr)
		w -= 2;
	if (!p->dash)
		ft_print_padding(p, w, ' ');
	if (!ptr)
		ft_putstr_buffer(p, "(nil)", 5);
	else
	{
		ft_putstr_buffer(p, "0x", 2);
		ft_putnbr_base_buffer(p, ptr, "0123456789abcdef");
	}
	if (p->dash)
		ft_print_padding(p, w, ' ');
}

void	handle_string(t_printf *p)
{
	char	*s;
	int		len;
	int		w;

	s = va_arg(p->args, char *);
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (p->dot && p->prec < len)
		len = p->prec;
	w = p->width - len;
	if (!p->dash)
		ft_print_padding(p, w, ' ');
	ft_putstr_buffer(p, s, len);
	if (p->dash)
		ft_print_padding(p, w, ' ');
}
