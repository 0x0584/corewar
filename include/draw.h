/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:31:27 by archid-           #+#    #+#             */
/*   Updated: 2021/01/22 11:56:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

#include <ncurses.h>

#include "vm.h"

#define DRAW_BUFF_SIZE			0x80
#define DRAW_LINE_SIZE			0x40
#define DRAW_LINE_WIDTH			0xC0 // SIZE * 3 characters `ff `

void			    draw_memory(void);

#endif
