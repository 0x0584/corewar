/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:19:10 by archid-           #+#    #+#             */
/*   Updated: 2021/01/22 11:29:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* https://stackoverflow.com/a/13707598 */
void handle_winch(int sig) {
	(void)sig;

	endwin();
	refresh();
	clear();
    mvprintw(0, 0, "COLS = %d, LINES = %d", COLS, LINES);
    for (int i = 0; i < COLS; i++)
        mvaddch(1, i, '*');
    refresh();
}


void draw_memory(void) {
    int		i;
	static char	buff[4] = {0};

	initscr();
	cbreak();
	noecho();
    i = 0;
    while (i < MEM_SIZE) {
		ft_snprintf(buff, 4, "%02x ", g_arena[i]);
		printw(buff);
		if (!((i + 1) % 0x40))
			printw("\n");
        i++;
    }
	refresh();
	while (getch());
	endwin();
}
