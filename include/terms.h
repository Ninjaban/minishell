/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 09:00:49 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/30 11:29:17 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMS_H
# define TERMS_H

/*
** # define LIM_HIST_ROW 3
** # define LIM_HIST_COL 115
**
** # define LIM_PROM_ROW 2
** # define LIM_PROM_COL 115
**
** # define LIM_FILE_ROW 5
** # define LIM_FILE_COL 115
**
** # define LIM_OUT_ROW 100
** # define LIM_OUT_COL 115
*/

# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

typedef char	t_bool;

typedef struct	s_win
{
	size_t		col;
	size_t		row;
	size_t		x;
	size_t		y;
}				t_win;

typedef struct	s_term
{
	t_bool		display;
	t_win		*history;
	t_win		*prompt;
	t_win		*files;
	t_win		*out;
	size_t		col;
	size_t		row;
}				t_term;

typedef struct 	s_display
{
	char		**history;
	char		**prompt;
	char		**files;
	char		**out;
	size_t		hist_iter;
}				t_display;

#endif
