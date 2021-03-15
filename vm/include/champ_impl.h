/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_impl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 09:33:56 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMP_IMPL_H
# define CHAMP_IMPL_H

# include "champ.h"
# include "memory.h"

t_st	champ_read(const char *filename, t_u8 player_idx, t_champ *champ);

#endif
