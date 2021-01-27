/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:55:22 by archid-           #+#    #+#             */
/*   Updated: 2021/01/25 09:10:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

inline t_u8			color(t_u16 at)
{
	assert(at < MEM_SIZE);
	return ((g_vm.colors[at] & 0x0f));
}

inline t_u8			color_effect(t_u16 at)
{
	assert(at < MEM_SIZE);
	return ((g_vm.colors[at] >> 4) ? ((g_vm.colors[at] >> 4) + color_count) : 0);
}

inline void			set_color(t_u8 clr, t_u16 at)
{
	assert(at < MEM_SIZE);
	g_vm.colors[at] = (g_vm.colors[at] & 0xf0) | (clr & 0x0f);
}

inline void			set_color_effect(t_u8 clr, t_u16 at)
{
	assert(at < MEM_SIZE);
	g_vm.colors[at] = (g_vm.colors[at] & 0x0f) | ((clr & 0x0f) << 4);
}

inline void		    resolve_color_effect(t_u16 at)
{
	assert(at < MEM_SIZE);
	g_vm.colors[at] >>= 4;
}

inline bool			has_mem_colors(t_u16 at)
{
	assert(at < MEM_SIZE);
	return g_vm.colors[at] != 0;
}
