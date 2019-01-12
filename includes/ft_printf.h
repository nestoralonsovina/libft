/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:23:56 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/12 15:39:52 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <stdio.h>

/*
** Different flag activation constants
*/

# define NONE (1 << 0)
# define CLEAR (1 << 1)
# define ZERO (1 << 2)
# define MINUS (1 << 3)
# define PLUS (1 << 4)
# define SPACE (1 << 5)
# define SHARP (1 << 6)
# define PRECISION (1 << 7)
# define NEGATIVE (1 << 8)

/*
** Color escape codes
*/

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

# define PF_BUFF_SIZE 64

typedef union		u_data
{
	int					i;
	unsigned int		ui;
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
	double				d;
	long double			ld;
	ssize_t				sst;
	size_t				st;
	intmax_t			imax;
	uintmax_t			uimax;
}					t_data;

typedef enum		e_modifiers
{
	NO, L, H, LL, HH, BIGL, Z, J
}					t_modifiers;

typedef enum		e_conversion
{
	NON, S, P, C, D, O, U, X, BIGX, B, F, N
}					t_conversion;

typedef struct		s_param
{
	char			*pf_string;
	char			conversion;
	char			*flags;
	int				width;
	int				precision;
	short			ind;
	t_modifiers		mod;
	t_conversion	conv;
	t_data			data;
}					t_param;

typedef struct		s_str
{
	char			str[PF_BUFF_SIZE];
	size_t			current_index;
	size_t			current_size;
}					t_str;

typedef struct		s_printf
{
	const char		*inp;
	int				len;
	t_str			buff;
	int 			fd;
	t_param			*curr;
}					t_printf;

int					ft_printf(const char *format, ...);
int					handle_args(const char *format, int fd, va_list arg);
int					handle_conversions(char flags[], va_list al);
int					colors(t_printf *p);

/*
**	USEFUL FUNCTIONS
*/

char				*fstrjoin(char *s1, char *s2);
void				*malloc_safe(size_t size);
char				*add_char(char *str, char c);
char				*data_to_base(t_param *node, int base);
char				*ft_strndup(const char *s1, size_t n);
char				*new_str(char c, int size);

/*
**	MANAGE PARAMETERS
*/


/*
** BUFFER MANAGEMENT
*/

void				reset_buffer(t_printf *p);
void				write_buffer(t_printf *p);
void				buffer(t_printf *p, void *data, size_t size);


t_param				*init_param(char *flags, va_list al);
char				ret_conversion(char *flags, t_param *curr);
int					is_conversion(char c);
void				search_width(t_param *new);
void				search_precision(t_param *new);
void				search_modifier(t_param *new);

/*
**	DEBUG
*/

void				set_conversion(char con, t_param *curr);
void				print_full_param(t_param curr);
char				*dec_to_hex(int nb);
void				print_reverse(char *str);
char				*ft_itoa_base(uintmax_t value, int base);
char				*ft_decimal_itoa(long long nbr);
char				*add_ind(char *str, t_param *node);
char				*add_prec(char *str, t_param *node);
void				handle_str(t_param *node, t_printf *p);
void				handle_ptr(t_param *node, t_printf *p);
void				handle_integer(t_param *node, t_printf *p);
void				handle_c(t_param *node, t_printf *head);
void				handle_float(t_param *a, t_printf *p);
void				handle_base(t_param *n, unsigned int base, t_printf *p);
void				handle_hexa(t_param *n, unsigned int base, t_printf *p);

#endif
