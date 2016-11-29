/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:49:46 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/29 16:44:33 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terms.h"
#include "error.h"
#include "shell.h"

static void		ft_init_size(t_term **term)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	(*term)->col = win.ws_col;
	(*term)->row = win.ws_row;
}

static t_win	*ft_init_win(size_t col, size_t row, size_t x, size_t y)
{
	t_win			*win;

	if ((win = malloc(sizeof(t_win))) == NULL)
		return (NULL);
	win->col = col;
	win->row = row;
	win->x = x;
	win->y = y;
	return (win);
}

t_term			*ft_init_term(void)
{
	t_term			*term;
	size_t			col;
	size_t			x;

	if ((term = malloc(sizeof(t_term))) == NULL)
		return (NULL);
	col = term->col / 2;
	term->display = (term->row > 10 && term->col > 50) ? TRUE : FALSE;
	term->history = ((term->row > 6 && col >= 50) || term->row > 27) ?
		ft_init_win(col, 3, 0, 0) : NULL;
	term->prompt = ((term->row > 6 && col >= 50) || term->row > 27) ?
		ft_init_win(col, 2, 0, 4) : ft_init_win(term->col, 2, 0, 0);
	term->files = (term->row > 12 && col >= 50) ?
		ft_init_win(col, term->row - 7, 0, 7) : NULL;
	term->out = (col >= 50) ?
		ft_init_win(col, term->row, col + 1, 0) : NULL;
	if (!term->out)
		term->out = (term->row > 27) ?
			ft_init_win(term->col, term->row - 7, 0, 7) :
			ft_init_win(term->col, term->row - 3, 0, 3);
	return (term);
}
