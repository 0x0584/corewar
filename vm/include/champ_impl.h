/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_impl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/02/25 09:49:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMP_IMPL_H
# define CHAMP_IMPL_H

# include "champ.h"
# include "memory.h"

/**
** \brief reads a champ from a file
**
** \param filename the .cor file
** \param player_idx index in `g_vm.arena`
**
** \return
**
**   - `st_succ` if champ is read
**   - otherwise `st_error` or`st_fail` are returned
*/
t_st				champ_read(const char *filename, t_u8 player_idx, t_champ *champ);

#endif
