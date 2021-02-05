/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:31:27 by archid-           #+#    #+#             */
/*   Updated: 2021/02/02 08:38:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "vm.h"

# include <ncurses.h>

# define DRAW_BUFF_SIZE									0X0F
# define DRAW_LINE_SIZE									0x40
# define DRAW_LINE_WIDTH								0XC0 // SIZE * 3 characters `ff `

/**
** \brief colors used for the drawing where the first variant indicat the player
** move and othe reversed variant indicated that he wrote over some other
** player's memory. it is used for visualizing the war.
**
** Each cell have
**
**		(color of write over) >> [0000][0000] << (owner's color)
**
** using a Byte to represent colors, each memory cell in `t_vm::arena` has a
** correponding color in `t_vm::memcolors` where the first 4 bytes indicate the
** player who has set the memory. at first all memory cells are fresh and
** initialized to `0`.
**
** At first, a player owns the cell by setting his color in the first 4-bits,
** then if another player is to set the cell, if the cell has no owner, then the
** player becomes the owner, else we keep the old owner and add a write over color
** of the player in the next 4-bits.
**
** \see memory.c
*/
enum				e_colors
{
	/* player colors */
    color_red_on_black = 1,
    color_green_on_black,
    color_yellow_on_black,
    color_cyan_on_black,

	color_count = color_cyan_on_black,

	/* effects */
    color_black_on_red,
    color_black_on_green,
    color_black_on_yellow,
    color_black_on_cyan,

	effect_count = color_count,
};

void			    draw_memory(void);


#endif
