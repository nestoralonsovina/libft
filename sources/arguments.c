/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:28:37 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/14 15:07:15 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		set_conversion(char con, t_param *curr)
{
	if (con == 's')
		curr->conv = S;
	else if (con == 'c')
		curr->conv = C;
	else if (con == 'p')
		curr->conv = P;
	else if (con == 'd' || con == 'D' || con == 'i')
		curr->conv = D;
	else if (con == 'f' || con == 'F')
		curr->conv = F;
	else if (con == 'o' || con == 'O')
		curr->conv = O;
	else if (con == 'u' || con == 'U')
		curr->conv = U;
	else if (con == 'x')
		curr->conv = X;
	else if (con == 'X')
		curr->conv = BIGX;
	else if (con == 'b')
		curr->conv = B;
	else
		curr->conv = NON;
}

void		parse_modifiers(t_printf *p)
{
	t_param *a;

	a = p->curr;
	a->mod = NO;
	while (42)
	{
		if (*p->inp == 'l')
			a->mod = (p->inp[1] == 'l' && ++p->inp) ? LL : L;
		else if (*p->inp == 'h')
			a->mod = (p->inp[1] == 'h' && ++p->inp) ? HH : H;
		else if (*p->inp == 'L')
			a->mod = BIGL;
		else if (*p->inp == 'z')
			a->mod = Z;
		else if (*p->inp == 'j')
			a->mod = J;
		else
			break ;
		++p->inp;
	}
}

void		parse_arg(t_printf *p, va_list al)
{
	t_param	*a;

	p->curr = (t_param *)malloc_safe(sizeof(t_param));
	p->curr->ind = 0;
	p->curr->width = 0;
	p->curr->precision = 1;
	a = p->curr;
	parse_flags(p);
	search_width_precision(p);
	parse_modifiers(p);
	parse_flags(p);
	//parse_options(p, al);
	if (*p->inp == '%')
	{
		p->curr->pf_string = add_ind(ft_strdup("%"), p->curr);
		buffer(p, p->curr->pf_string, ft_strlen(p->curr->pf_string));
	}
	else if (*p->inp == 'n')
	{
		*va_arg(al, int *) = p->len;
	}
	else if (ft_strchr("bcspdiouxXfFODU", *p->inp) == NULL || !*p->inp)
	{
		if (*p->inp)
			buffer(p, (void *)p->inp, 1);
	}
	else if (*p->inp)
	{
		if (ft_strchr("ODU", *p->inp) != NULL)
			p->curr->mod = p->curr->mod == L ? LL : L;
		set_conversion(*p->inp, p->curr);
		if ((p->curr->ind & ZERO) && (p->curr->ind & PRECISION) \
				&& p->curr->conv != C && p->curr->conv != S && p->curr->conv != F)
		{
			p->curr->ind &= ~ZERO;
			p->curr->ind |= CLEAR;
		}
		search_arg(p->curr, al);
		convert_arg(p);
	}
	free(a);
}

int			handle_args(const char *format, int fd, va_list al)
{
	t_printf	p;

	p.inp = format;
	p.len = 0;
	p.fd = fd;
	reset_buffer(&p);
	while (*p.inp)
	{
		if (*p.inp == '%')
		{
			++p.inp;
			if (!*p.inp)
				break ;
			parse_arg(&p, al);
		}
		else if (!(colors(&p)))
		{
			buffer(&p, (void *)p.inp, 1);
		}
		++p.inp;
	}
	write_buffer(&p);
	return (p.len);
}
