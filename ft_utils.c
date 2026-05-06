/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:17:42 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/06 15:56:40 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_print_padding(t_printf *p, int count, char c)
{
	while (count-- > 0)
		add_to_buffer(p, c);
}

int	ft_get_num_len(unsigned long n, int base_len)
{
	int	len;

	len = 1;
	while (n >= (unsigned long)base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

void	ft_putstr_buffer(t_printf *p, char *s, int len)
{
	while (*s && len-- > 0)
	{
		add_to_buffer(p, *s);
		s++;
	}
}

void	ft_putnbr_base_buffer(t_printf *p, unsigned long n, char *base)
{
	unsigned long	blen;

	blen = ft_strlen(base);
	if (n >= blen)
		ft_putnbr_base_buffer(p, n / blen, base);
	add_to_buffer(p, base[n % blen]);
}
