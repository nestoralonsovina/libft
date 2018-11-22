/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:23:56 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/22 14:58:53 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <locale.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdio.h>

// diouxX

typedef union	u_data
{
	int					i;
	float				f;
	char				c;
	void				*ptr;
	char				*str;
	signed char			sc;
	unsigned char		uc;
	short				s;
	unsigned short		us;
	long				l;
	long long			ll;
	unsigned long		ul;
	unsigned long long	ull;
}				t_data;

typedef enum	e_modifiers
{
	NO = 0, L = 1, H = 2, LL = 3, HH = 4, BIGL = 5
}				t_modifiers;

typedef enum	e_indentation
{
	NONE = 0, CLEAR = 1, ZERO = 2
}				t_indentation;

// not utilized par l'instant
typedef enum	e_conversion
{
	NON, S, P, C, D, I, O, U, X, BIGX, F
}				t_conversion;

typedef struct	s_param 
{
	char			*pf_string;
	char			conversion;
	char			*flags;
	int				width;
	int				precision;
	t_indentation	ind;
	t_modifiers		mod;
	t_conversion	conv;
	t_data			data;
}				t_param;

typedef struct	s_printf
{
	char			*buff;
	t_param			*curr;
}				t_printf;

int				ft_printf(const char *format, ...);
char			*handle_args(const char *format, va_list arg);
int				handle_conversions(char flags[], va_list al);

/*
**	USEFUL FUNCTIONS
*/

char			*fstrjoin(char *s1, char *s2);
void			*malloc_safe(size_t size);
char			*add_char(char *str, char c);

/*
**	MANAGE PARAMETERS
*/

t_param		*init_param(char *flags, va_list al);
char		ret_conversion(char *flags, t_param *curr);
int			is_conversion(char c);
void		search_width(t_param *new);
void		search_precision(t_param *new);
void		search_modifier(t_param *new);

/*
**	DEBUG
*/

/*  How each flag affects depending on the conversion
	Modifier          d, i           o, u, x, X        
	hh                signed char    unsigned char     
	h                 short          unsigned short    
	l (ell)           long           unsigned long     
	ll (ell ell)      long long      unsigned long long
*/
 
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

void		print_full_param(t_param curr);
char		*dec_to_hex(int nb);
void		print_reverse(char *str);

// FUNCTIONS TO HANDLE DIFFERENT FLAGS

char			*add_ind(char *str, t_param *node);
void			handle_str(t_param *node);
/*
int				handle_str(char *flags, char *str);
int				handle_char(char *flags, char c);
int				handle_ptr(char *flags, void *ptr);
int				handle_long(char *flags, va_list al);
int				handle_int(char *flags, va_list al);
int				handle_float(char *flags, va_list al);
int				handle_octal(char *flags, va_list al);
int				handle_decimal(char *flags, va_list al);
int				handle_hexa(char *flags, va_list al);
*/
#endif