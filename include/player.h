/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/01/19 14:55:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "common.h"
# include "address.h"

typedef t_u8			*t_cor;
typedef struct s_player t_player;

struct					s_player
{
	t_header	hdr;			/* file header */
	t_cor		file;			/* the foo.cor */
	t_addr		*pc;			/* program counter */
	t_addr		*mar;			/* memory address register */
};

extern bool player_debug;

#endif
