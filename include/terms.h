/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 09:00:49 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/29 09:23:56 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMS_H
# define TERMS_H

# include <sys/ioctl.h>

typedef char	t_bool;

typedef struct	s_win
{
	t_bool		display;
	size_t		col;
	size_t		row;
}				t_win;

typedef struct	s_term
{
	t_bool		display;
	t_win		*history;
	t_win		*prompt;
	t_win		*files;
	t_win		*out;
}				t_term

#endif
