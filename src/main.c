/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:01:05 by archid-           #+#    #+#             */
/*   Updated: 2021/01/21 18:13:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "draw.h"

int main(int argc, char *argv[])
{
	if (!parse_arguments(argc, argv))
		return (-1);
    mem_load();
    draw_memory();
    return (0);
}
