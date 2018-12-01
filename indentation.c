#include "ft_printf.h"

char	*new_str(char c, int size)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc_safe(sizeof(char) * size);
	while (i < size)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

char	*add_ind(char *str, t_param *node)
{
	int		len;
	char	*new;
	char	*ind;

	len = ft_strlen(str);
	if (len >= node->width)
		return (str);
	else
	{
		if (node->ind == CLEAR || node->conv == P || node->conv == C || ft_strchr(node->flags, '-'))
			ind = new_str(' ', node->width - len);
		else
			ind = new_str('0', node->width - len);
		if (ft_strchr(node->flags, '-'))
			new = fstrjoin(str, ind);
		else
			new = fstrjoin(ind, str);
		return (new);
	}
}

char	*add_prec(char *str, t_param *node)
{
	int		len;
	char	*new;

	if (node->ind == ZERO && node->precision > -1)
		node->ind = CLEAR;
	len = ft_strlen(str);
	if (node->precision == 0)
		return (ft_strdup(""));
	if (len >= node->precision)
		return (str);
	else
		new = fstrjoin(new_str('0', node->precision - len), str);
	return (new);
}
