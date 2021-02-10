/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:41:40 by archid-           #+#    #+#             */
/*   Updated: 2021/02/10 14:50:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void    fork_(t_proc proc)
{
	ft_printf("op fork");
	(void)proc;
}

void    lfork(t_proc proc)
{
	ft_printf("op lfork");
	(void)proc;
}
