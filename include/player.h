/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/01/12 17:31:19 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "common.h"
# include "address.h"

typedef unsigned char	*t_cor;
typedef struct s_player t_player;

struct					s_player
{
	t_cor		blob;
	t_addr		*pc;
	t_addr		*mar;			// memory address register
};

#endif
