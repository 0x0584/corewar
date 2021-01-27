/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/01/25 09:33:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vmtypes.h"
# include "process.h"

/**
** \brief a champion if the resulted .cor file, it has a header and instructions
**
** \see op.h
** \see vmtypes.h
*/
typedef struct				s_champ
{
	/**
	** \brief file header describes the core file
	*/
	t_header	hdr;

	/**
	** \brief .cor executable instructions
	*/
	t_cor		file;
}							t_champ;

/**
** \brief a player has a .cor file and is running on a process `t_player::prog`
*/
typedef struct				s_player
{
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
** \param p pointer to the player of `g_gladiators`
**
** \return `st_succ` if player is read, otherwise `st_error` or `st_fail` are
** returned
*/
t_st				player_read(const char *filename, t_player *p);

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
extern bool					g_player_debug;

#endif
