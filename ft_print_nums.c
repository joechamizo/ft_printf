/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:26:06 by joaqumar          #+#    #+#             */
/*   Updated: 2026/04/25 14:27:13 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// 1. Determina el prefijo (+, -, espacio) y maneja el número negativo
static char	*get_int_prefix(t_printf *p, long *n)
{
	if (*n < 0)
	{
		*n = -(*n);
		return ("-");
	}
	if (p->plus)
		return ("+");
	if (p->space)
		return (" ");
	return ("");
}

// 2. Imprime el bloque: Prefijo + Ceros de precisión + Número
static void	print_int_box(t_printf *p, long n, char *pref, int zeros)
{
	int	n_len;

	n_len = ft_get_num_len(n, 10);
	if (n == 0 && p->dot && p->prec == 0)
		n_len = 0;
	// Si hay flag '0' y NO hay precisión, el padding de ceros va después del signo
	if (p->zero && (!p->dot || p->prec < 0))
	{
		ft_putstr_buffer(p, pref, 3); // 3 es un límite seguro para el prefijo
		ft_print_padding(p, p->width - (ft_strlen(pref) + zeros + n_len), '0');
	}
	else
	{
		ft_putstr_buffer(p, pref, 3);
	}
	ft_print_padding(p, zeros, '0');
	if (n_len > 0)
		ft_putnbr_base_buffer(p, n, "0123456789");
}

// 3. Handler para %d e %i
void	handle_int(t_printf *p)
{
	long	n;
	char	*pref;
	int		n_len;
	int		zeros;
	int		width_pad;

	n = (long)va_arg(p->args, int);
	pref = get_int_prefix(p, &n);
	n_len = ft_get_num_len(n, 10);
	if (n == 0 && p->dot && p->prec == 0)
		n_len = 0;
	zeros = 0;
	if (p->prec > n_len)
		zeros = p->prec - n_len;
	width_pad = p->width - (ft_strlen(pref) + zeros + n_len);
	// Padding inicial (espacios)
	if (!p->dash && (!p->zero || (p->dot && p->prec >= 0)))
		ft_print_padding(p, width_pad, ' ');
	print_int_box(p, n, pref, zeros);
	// Padding final (si hay flag '-')
	if (p->dash)
		ft_print_padding(p, width_pad, ' ');
}

// 4. Handler para %u (unsigned int)
void	handle_unsigned(t_printf *p)
{
	unsigned int	n;
	int				n_len;
	int				zeros;
	int				width_pad;

	n = va_arg(p->args, unsigned int);
	n_len = ft_get_num_len(n, 10);
	if (n == 0 && p->dot && p->prec == 0)
		n_len = 0;
	zeros = 0;
	if (p->prec > n_len)
		zeros = p->prec - n_len;
	width_pad = p->width - (zeros + n_len);
	if (!p->dash && (!p->zero || (p->dot && p->prec >= 0)))
		ft_print_padding(p, width_pad, ' ');
	if (!p->dash && p->zero && (!p->dot || p->prec < 0))
		ft_print_padding(p, width_pad, '0');
	ft_print_padding(p, zeros, '0');
	if (n_len > 0)
		ft_putnbr_base_buffer(p, n, "0123456789");
	if (p->dash)
		ft_print_padding(p, width_pad, ' ');
}
