/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:22:33 by archid-           #+#    #+#             */
/*   Updated: 2021/02/06 12:23:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMP_H
# define CHAMP_H

# include "op.h"

/**
** \brief each `.cor` file must have a valid header a core file is a blob of Bytes
**
** \see const.h
*/
typedef struct				s_champ
{
	/**
	** \brief a 4-Bytes indicator
	*/
	t_u32		magic;

	/**
	** \brief a program name has at most `PROG_NAME_LENGTH`
	**
	**   padded with `\0` if less
	*/
	t_u8		prog_name[PROG_NAME_LENGTH + 1];

	/**
	** \brief 4-Bytes indicating the total program size
	**
	**   excluding `magic`, `prog_name` and `comment`
	*/
	t_u32		prog_size;

	/**
	 ** \brief program comment is at most `COMMENT_LENGTH`
	 **
	 **   also padded with `\0` if less
	 */
	t_u8		comment[COMMENT_LENGTH + 1];

	/**
	** \brief .cor executable instructions
	*/
	t_u8		file[CHAMP_MAX_SIZE + 1];
}							t_champ;

#endif
