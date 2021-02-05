/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/02/05 18:10:37 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

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
	** \brief champion of the player
	*/
	t_champ		champ;

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
t_st				player_read(const char *filename, t_u8 player_num);

/**
** \brief output player information
**
** \param p player
*/
void				player_dump(t_player *p);

/*
** Global Variables
*/

/**
** \brief if set to `true`, player functions output debugging information
*/
extern bool			g_player_debug;

#endif
