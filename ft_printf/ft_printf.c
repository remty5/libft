/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:31:58 by rvandepu          #+#    #+#             */
/*   Updated: 2023/12/21 21:24:22 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int (*const	g_spec[])(t_flags *flags, va_list args) = {\
	['d'] = &ft_spec_dec, \
	['i'] = &ft_spec_dec, \
	['u'] = &ft_spec_uns, \
	['o'] = &ft_spec_oct, \
	['x'] = &ft_spec_hex, \
	['X'] = &ft_spec_hex_upper, \
	['c'] = &ft_spec_char, \
	['s'] = &ft_spec_string, \
	['p'] = &ft_spec_ptr, \
	['%'] = &ft_spec_percent, \
};

int	ft_vprintf(const char *format, va_list args)
{
	t_flags	flags;
	int		next;

	ft_bzero(&flags, sizeof(t_flags));
	next = ft_next_spec(format);
	if (next)
		return (ft_printstr(&flags, format, next)
			+ ft_vprintf(format + next, args));
	next = ft_parse_spec(format, args, &flags);
	if (next)
		return (g_spec[(int)flags.spec](&flags, args)
			+ ft_vprintf(format + next, args));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vprintf(format, args);
	va_end(args);
	return (ret);
}
