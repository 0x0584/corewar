/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/02/25 09:49:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "champ.h"
# include "op_impl.h"

/**
** \brief reads a player from a file
**
** \param filename the .cor file
** \param player_num index in `g_vm.arena`
**
** \return
**
**   - `st_succ` if player is read
**   - otherwise `st_error` or`st_fail` are returned
*/
t_st				player_read(const char *filename, t_u8 player_num, t_champ *champ);

#endif
