/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:19:10 by archid-           #+#    #+#             */
/*   Updated: 2021/02/06 12:18:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "color.h"

/* https://stackoverflow.com/a/13707598 */
void		handle_winch(int sig) {
	(void)sig;

	endwin();
	refresh();
	clear();
    mvprintw(0, 0, "COLS = %d, LINES = %d", COLS, LINES);
    for (int i = 0; i < COLS; i++)
        mvaddch(1, i, '*');
    refresh();
}

static void draw_setup(void)
{
	initscr();
	start_color();
	init_pair(color_red_on_black, COLOR_RED, COLOR_BLACK);
	init_pair(color_green_on_black, COLOR_GREEN, COLOR_BLACK);
	init_pair(color_cyan_on_black, COLOR_CYAN, COLOR_BLACK);
	init_pair(color_yellow_on_black, COLOR_YELLOW, COLOR_BLACK);
	init_pair(color_black_on_yellow, COLOR_BLACK, COLOR_YELLOW);
	init_pair(color_black_on_red, COLOR_BLACK, COLOR_RED);
	init_pair(color_black_on_cyan, COLOR_BLACK, COLOR_CYAN);
	init_pair(color_black_on_green, COLOR_BLACK, COLOR_GREEN);
	cbreak();
	noecho();
}

static void draw_loop()
{
	refresh();
	while (getch());
	endwin();
}

void		draw_memory(void)
{
    int			i;
	static char	buff[DRAW_BUFF_SIZE] = {0};

    draw_setup();
    i = 0;
    while (i < MEM_SIZE)
	{
		ft_snprintf(buff, DRAW_BUFF_SIZE, "%02x", g_vm.arena[i]);
		attron(COLOR_PAIR(color(i)));
		ft_dprintf(g_fd, " >> owner of %4d is %08b\n", i, g_vm.colors[i]);
		printw(buff);
		attroff(COLOR_PAIR(color(i)));
		printw(" ");
		if (!(++i % DRAW_LINE_SIZE))
			printw("\n");
    }
	draw_loop();
}
