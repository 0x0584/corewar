/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:22:33 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 10:44:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMP_H
# define CHAMP_H

# include "op.h"

typedef struct				s_champ
{
	t_u32		magic;
	t_u8		prog_name[PROG_NAME_LENGTH + 1];
	t_u32		prog_size;
	t_u8		comment[COMMENT_LENGTH + 1];
	t_u8		file[CHAMP_MAX_SIZE + 1];
}							t_champ;

#endif
