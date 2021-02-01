/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:54:02 by archid-           #+#    #+#             */
/*   Updated: 2021/01/29 15:10:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "draw.h"

t_u8				color(t_u16 at);
t_u8				color_effect(t_u16 at);

void				set_color(t_u8 clr, t_u16 at);
void				set_color_effect(t_u8 clr, t_u16 at);
void			    resolve_color_effect(t_u16 at);

bool				has_mem_colors(t_u16 at);
bool				changed_mem_colors(t_u16 at);

#endif
