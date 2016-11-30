/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 09:40:00 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/30 13:21:46 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terms.h"
#include "error.h"
#include "shell.h"

static void	ft_putnbchar(char c, size_t nb)
{
	while (nb-- > 0)
		ft_putchar(c);
}

static void	ft_putstr_lim(char *str, size_t lim)
{
	write(1, str, (ft_strlen(str) > lim) ? lim : ft_strlen(str));
}

static void	ft_display_history(t_term *term, t_display *disp,
								size_t *x, size_t *y)
{
	if (disp->history && disp->hist_iter >= 0)
	{
		ft_goto("cm", (*x) + 1, (*y)++);
		ft_putstr_lim(disp->history[hist_iter], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
		if (hist_iter > 0)
		{
			ft_goto("cm", (*x) + 1, (*y)++);
			ft_putstr_lim(disp->history[hist_iter - 1], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
		}
		if (hist_iter > 1)
		{
			ft_goto("cm", (*x) + 1, (*y)++);
			ft_putstr_lim(disp->history[hist_iter - 2], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
		}
		ft_goto("cm", (*x) + 1, (*y)++);
		ft_putnbchar('-', (term->col / 2 >= 50) ? term->col / 2 : term->col);
	}
}

static void	ft_display_prompt(t_term *term, t_display *disp,
							  size_t *x, size_t *y)
{
	ft_goto("cm", (*x) + 1, (*y)++);
	ft_putstr_lim(disp->prompt[0], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
	if (disp->prompt[1])
	{
		ft_goto("cm", (*x) + 1, (*y)++);
		ft_putstr_lim(disp->prompt[1], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
	}
	if (term->files || term->col / 2 < 50)
	{
		ft_goto("cm", (*x) + 1, (*y)++);
		ft_putnbchar('-', (term->col / 2 >= 50) ? term->col / 2 : term->col);
	}
}

static void	ft_display_files(t_term *term, t_display *disp,
							 size_t *x, size_t *y)
{
	size_t	n;

	n = 0;
	if (disp->files)
	{
		while ((*y) < term->row - 1 && disp->files[n])
		{
			ft_goto("cm", (*x) + 1, (*y)++);
			ft_putstr_lim(disp->files[n++], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
		}
	}
}

static void	ft_display_out(t_term *term, t_display *disp,
							 size_t *x, size_t *y)
{
	size_t	n;

	n = 0;
	if (disp->out)
	{
		if (ft_tablen(out) <= term->row - 1)
			while (disp->out[n])
			{
				ft_goto("cm", (*x) + 1, (*y)++);
				ft_putstr_lim(disp->files[n++], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
			}
		else
		{
			n = ft_tablen(disp->out);
			(*y) = term->row;
			while (y > 0)
			{
				ft_goto("cm", (*x) + 1, (*y) - 1);
				ft_putstr_lim(disp->files[--n], (term->col / 2 >= 50) ? term->col / 2 - 2 : term->col - 2);
				(*y) = (*y) - 1;
			}
		}
	}
}

void		ft_display(t_term *term, t_display *disp)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	ft_goto("clear", 1, 1);
	if (!term)
		return ;
	if (term->history)
		ft_display_history(term, disp, &x, &y);
	ft_display_prompt(term, disp, &x, &y);
	if (term->files)
		ft_display_files(term, disp, &x, &y);
	y = 0;
	x = (term->col / 2 >= 50) ? term->col / 2 : term->col;
	ft_display_out(term, disp, &x, &y);
}
