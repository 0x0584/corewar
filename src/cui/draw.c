/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:19:10 by archid-           #+#    #+#             */
/*   Updated: 2021/01/23 17:44:51 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	init_pair(color_black_on_white, COLOR_BLACK, COLOR_WHITE);
	init_pair(color_black_on_red, COLOR_BLACK, COLOR_RED);
	init_pair(color_red_on_black, COLOR_RED, COLOR_BLACK);
	init_pair(color_blue_on_green, COLOR_BLUE, COLOR_GREEN);
	init_pair(color_green_on_blue, COLOR_GREEN, COLOR_BLUE);
	init_pair(color_cyan_on_magenta, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(color_magenta_on_cyan, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(color_white_on_yellow, COLOR_WHITE, COLOR_YELLOW);
	init_pair(color_yellow_on_white, COLOR_YELLOW, COLOR_WHITE);
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

    i = 0;
    draw_setup();
    while (i < MEM_SIZE)
	{
		ft_snprintf(buff, DRAW_BUFF_SIZE, "%02x ", g_arena[i]);
		attron(COLOR_PAIR(color_owner(i)));
		if (color_writer(i))
		{
			ft_putendl("...");
			refresh();
			attron(color_writer(i));
			refresh();
		}
		printw(buff);
		attroff(COLOR_PAIR(color_owner(i)));
		if (!(++i % DRAW_LINE_SIZE))
			printw("\n");
    }
	draw_loop();
}
