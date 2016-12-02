/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:34:29 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/01 14:25:12 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terms.h"
#include "error.h"
#include "shell.h"

/*
**	clear	=	efface l'ecran.
**	vi		=	curseur invisible.
**	ve		=	curseur visible.
**	cm		=	deplacer le curseur.
**	us		=	debut souligner.
**	ue		=	fin souligner.
*/

int			fputchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int			ft_goto(char *cmd, int col, int line)
{
	char	*str;

	str = NULL;
	if ((str = tgoto(tgetstr(cmd, NULL), col, line)) == NULL)
		return (FALSE);
	tputs(str, 1, fputchar);
	if (str)
		free(str);
	return (TRUE);
}

int			ft_termcaps_end(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (FALSE);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (FALSE);
	return (TRUE);
}

int			ft_termcaps_init(void)
{
	struct termios	term;
	const char		*name;

	if ((name = getenv("TERM")) == NULL)
		return (FALSE);
	if (tgetent(NULL, name) != 1)
	{
		free((char *)name);
		return (FALSE);
	}
	free((char *)name);
	if (tcgetattr(0, &term) == -1)
		return (FALSE);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (FALSE);
	return (TRUE);
}
