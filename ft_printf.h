/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:47:35 by joaqumar          #+#    #+#             */
/*   Updated: 2026/04/25 14:38:46 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define BUF_SIZE 4096

typedef struct s_printf
{
	va_list	args;
	char	buffer[BUF_SIZE];
	int		index;
	int		total_len;
	int		dash;
	int		zero;
	int		dot;
	int		prec;
	int		width;
	int		hash;
	int		plus;
	int		space;
	char	type;
}	t_printf;

int		ft_printf(const char *format, ...);

void	add_to_buffer(t_printf *p, char c);
void	reset_flags(t_printf *p);
void	flush_buffer(t_printf *p);

int		ft_parse_flags(const char *str, int i, t_printf *p);
int		ft_isdigit(int c);
int		ft_atoi_simple(const char *str, int *i);

void	handle_conversions(t_printf *p);
void	handle_char(t_printf *p);
void	handle_string(t_printf *p);
void	handle_int(t_printf *p);
void	handle_unsigned(t_printf *p);
void	handle_hex(t_printf *p);
void	handle_pointer(t_printf *p);
void	handle_percent(t_printf *p);

void	ft_putstr_buffer(t_printf *p, char *s, int len);
void	ft_putnbr_base_buffer(t_printf *p, unsigned long n, char *base);
void	ft_print_padding(t_printf *p, int count, char c);
int		ft_get_num_len(unsigned long n, int base_len);
size_t	ft_strlen(const char *s);

#endif
