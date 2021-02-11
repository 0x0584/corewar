/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/02/06 12:23:05 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "op.h"
# include "champ.h"

/**
** \brief a player has a .cor file and is running on a process `t_player::prog`
*/
typedef struct				s_player
{
	/**
	** \brief a program name has at most `PROG_NAME_LENGTH`
	**
	**   padded with `\0` if less
	*/
	t_u8		prog_name[PROG_NAME_LENGTH + 1];

	/**
	** \brief the main process on which the player executes instructions
	*/
	t_proc		prog;
}							t_player;

/**
** \brief reads a player from a file
**
** \param filename the .cor file
** \param player_num index in `g_vm.arena`
**
** \return `st_succ` if player is read, otherwise `st_error` or `st_fail` are
** returned
*/
t_st				player_read(const char *filename, t_u8 player_num,
								t_player *player);

#endif
